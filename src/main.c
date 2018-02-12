#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include <machine/int86.h>
#include "main.h"

unsigned long g_key_code = 0;  /**<@brief key code received from the keyboard */
unsigned long g_timer_cnt = 0; /**<@brief timer tick counter */
unsigned long g_counter;       /**<@brief number of packets read */
unsigned long g_packet[3];     /**<@brief array that stores the packets received from the mouse */

void state_machine(State_Machine *st)
{
	int score = 0;

	while(st->current_state != end)
	{
		switch(st->current_state)
		{
		case play:

			if((st->next_event == esc_press) || (st->next_event == lost_game))
				{
					st->current_state = game_over_s;
					st->next_event = null;
				}

			break;

		case init:

			if(st->next_event == null)
				Main_Menu(st);

			if(st->next_event == start_b)
			{
				st->current_state = play;
				score = cycle(st);
			}

			if(st->next_event == exit_b)
				st->current_state = end;

			break;

		case game_over_s:

			g_key_code = 0;

			if(st->next_event == esc_press)
			{
				st->current_state = init;
				st->next_event = null;
			}
			else
				game_over(score, st);


			break;

		default:
			break;
		}
	}

}



int cycle(State_Machine *st)
{

	short ch_x = CHARACTER_X0, ch_y = CHARACTER_Y0;

	Bitmap *bitmaps_game[4];
	create_bitmaps_game(bitmaps_game);

	Server *server_array[4];
	create_serverArray(server_array);
	int n_servers = sizeof(server_array)/sizeof(server_array[0]);

	draw_map(bitmaps_game, server_array, n_servers);
	drawBitmap_pixels(bitmaps_game[1], ch_x, ch_y, ALIGN_LEFT);
	buffer_cpy();

	int k_hook_bit = kbc_subscribe(), r, ipc_status;
	int t_hook_bit = timer_subscribe_int();
	int sec_cnt = 0, sec_cnt_2 = 0;
	int score = 0;
	int break_time = 10;
	int break_point = 0;
	int serverID = -1;
	int i;
	message msg;

	while((st->next_event != esc_press) && (st->next_event != lost_game)) //Ends when ESC key is pressed or all servers are broken
		{

			if((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
			{
				printf("driver_receive failed with: %d", r);
				continue;
			}

			if(is_ipc_notify(ipc_status))
			{
				switch(_ENDPOINT_P(msg.m_source))
				{
					case HARDWARE:

						if(msg.NOTIFY_ARG & k_hook_bit)
						{
							C_kbd_handler();

							if(g_key_code == ESC_BR)
								st->next_event = esc_press;
						}

						if(msg.NOTIFY_ARG & t_hook_bit)
						{
							timer_int_handler();
							move(&ch_x, &ch_y, bitmaps_game, server_array, n_servers);
							buffer_cpy();

							//serverID is the identifier that shows what server the character centre is in colision with
							serverID = check_colision(ch_x + bitmaps_game[1]->bitmapInfoHeader.width / 2, ch_y + bitmaps_game[1]->bitmapInfoHeader.height / 2, server_array, n_servers);

							//If the player presses the E key and is in colision with a server (through check_colision()), the server will be fixed

							if(g_key_code == E_SC && serverID != -1)
							{

								fix_server(server_array, n_servers, serverID, &score);
								drawBitmap(bitmaps_game[2], server_array[serverID]->x_coord, server_array[serverID]->y_coord, ALIGN_LEFT);
								drawBitmap_pixels(bitmaps_game[1], ch_x, ch_y, ALIGN_LEFT);
								buffer_cpy();
							}

							if(g_timer_cnt % MINIX_FREQ == 0)
							{
								sec_cnt++;
								sec_cnt_2++;

								if(sec_cnt == break_time)
								{
									sec_cnt = 0;
									break_point = break_server(server_array, n_servers);
									buffer_cpy();

									if(break_point)
									{
										st->next_event = lost_game;
										break;
									}
								}

								if((sec_cnt_2 % 20 == 0) && (sec_cnt_2 > 0))
								{
									score += 20;

									if(break_time - 2 > 0)
										break_time -= 2;
									else
										break_time = 1;

								}

							}
						}
						break;

					default:
						break;
				}
			}
			else
				printf("Received a standard message, not a notification.\n");

			tickdelay(micros_to_ticks(DELAY_US));
		}

	if(kbc_unsubscribe() != 0)
		return -1;

	if(timer_unsubscribe_int() != 0)
		return -1;

		for(i = 0; i < n_servers; i++) {

			delete_server(server_array[i]);
		}


	return score;
}


void Main_Menu(State_Machine *st)
{
	int m_hook_bit = mouse_subscribe(), r, ipc_status;
	int mx_coord = 500, my_coord = 300;
	int t_hook_bit = timer_subscribe_int();
	unsigned long trash, status_byte, packet_byte;
	message msg;

	Bitmap* bitmaps_MainMenu[6];
	create_bitmaps_MainMenu(bitmaps_MainMenu);


	draw_menu(bitmaps_MainMenu);
	buffer_cpy();


	if(sys_inb(STAT_REG, &status_byte) != 0) //Reads from status register
	{
		printf("Error in reading status register in mouse_handler\n");
		return;
	}

	if(status_byte & OBF)
		sys_inb(OUT_BUF, &trash);

	if(write_mouse(EN_STREAM_M) == 0xFE)
		if(write_mouse(EN_STREAM_M) == 0xFC)
		{
			printf("Second consecutive invalid byte\n");
			return;
		}

	if(write_mouse(EN_DATA_REP) == 0xFE)
		if(write_mouse(EN_DATA_REP) == 0xFC)
		{
			printf("Second consecutive invalid byte\n");

			return;
		}

	if(sys_inb(STAT_REG, &status_byte) != 0) //Reads from status register
	{
		printf("Error in reading status register in mouse_handler\n");
		return;
	}

	if(status_byte & OBF)
		sys_inb(OUT_BUF, &trash);

	g_counter = 0;

		while(st->next_event == null)
		{
			if((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
			{
				printf("driver_receive failed with: %d", r);
				continue;
			}

			if(is_ipc_notify(ipc_status))
			{
				switch(_ENDPOINT_P(msg.m_source))
				{
				case HARDWARE:
					if(msg.NOTIFY_ARG & m_hook_bit)
					{
						M_ASM_IH();

						if(sys_inb(OUT_BUF, &packet_byte) != 0) //Reads packet byte from out_buf
							return;

						if((g_counter > 0) || (packet_byte & BIT(3)))//If bit 3 of the first byte is not set ...
						{
							g_packet[g_counter] = packet_byte;
							g_counter++;
						}

						if(g_counter == 3)
						{
							update_coords(g_packet, &mx_coord, &my_coord);
							draw_menu(bitmaps_MainMenu);
							drawBitmap_pixels(bitmaps_MainMenu[5], mx_coord, my_coord, ALIGN_LEFT);
							buffer_cpy();
							g_counter = 0;
						}


					}

					if(msg.NOTIFY_ARG & t_hook_bit)
					{

							if((mx_coord >= start_button_x)
									&& (mx_coord <= start_button_x + bitmaps_MainMenu[3]->bitmapInfoHeader.width)
									&& (my_coord >= start_button_y)
									&& (my_coord <= start_button_y + bitmaps_MainMenu[3]->bitmapInfoHeader.height)
									&& ((g_packet[0] & LB) == LB))
								st->next_event = start_b;

							if((mx_coord >= exit_button_x)
									&& (mx_coord <= exit_button_x + bitmaps_MainMenu[4]->bitmapInfoHeader.width)
									&& (my_coord >= exit_button_y)
									&& (my_coord <= exit_button_y + bitmaps_MainMenu[4]->bitmapInfoHeader.height)
									&& ((g_packet[0] & LB) == LB))
								st->next_event = exit_b;


					}
					break;

				default:
					break;
				}
			}
			else
				printf("Received a standard message, not a notification.\n");

			tickdelay(micros_to_ticks(DELAY_US));
		}

		if(write_mouse(DIS_DATA_REP) == 0xFE)
			if(write_mouse(DIS_DATA_REP) == 0xFC)
			{
				printf("Second consecutive invalid byte\n");
				return;
			}

		if(mouse_unsubscribe() != 0)
			return;

		if(timer_unsubscribe_int() != 0)
				return;

		if(sys_inb(STAT_REG, &status_byte) != 0)
			return;

		if((status_byte & OBF) == OBF)
			sys_inb(OUT_BUF, &trash);

}

void print_score(int score, Bitmap *bitmaps_endScreen[]) {

	int score_digit;
	short x0 = 550;

	if(score == 0)
		drawBitmap_pixels(bitmaps_endScreen[0], x0, 200, ALIGN_LEFT);

	while(score > 0) {
		score_digit = score % 10;
		drawBitmap_pixels(bitmaps_endScreen[score_digit], x0, 200, ALIGN_LEFT);
		x0 -= 36;
		score /= 10;

	}
}

void game_over(int score, State_Machine *st)
{

	Bitmap *bitmaps_endScreen[11];
	create_bitmaps_endScreen(bitmaps_endScreen);

	int k_hook_bit = kbc_subscribe(), r, ipc_status;
	message msg;

	drawBitmap_pixels(bitmaps_endScreen[10], 512, 10, ALIGN_CENTER);

	print_score(score, bitmaps_endScreen);

	buffer_cpy();

	while(st->next_event != esc_press)
			{

				if((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
				{
					printf("driver_receive failed with: %d", r);
					continue;
				}

				if(is_ipc_notify(ipc_status))
				{
					switch(_ENDPOINT_P(msg.m_source))
					{
						case HARDWARE:

							if(msg.NOTIFY_ARG & k_hook_bit)
								C_kbd_handler();


							if(g_key_code == ESC_BR)
								st->next_event = esc_press;

							break;

						default:
							break;
					}
				}
				else
					printf("Received a standard message, not a notification.\n");

				tickdelay(micros_to_ticks(DELAY_US));
			}

		kbc_unsubscribe();
}

int main()
{
	sys_enable_iop(SELF);
	vg_init(0x117);
	State_Machine st;
	st.current_state = init;
	st.next_event = null;
	state_machine(&st);
	vg_exit();

	return 0;
}
