#include "Mouse_reusable.h"

int g_m_hook_id = 12;

void update_coords(unsigned long packet[], int *xi, int *yi)
{
	unsigned h_res = get_hres(), v_res = get_vres();
	int v_x = (int) packet[1], v_y = (int) packet[2];

	if((packet[0] & X_SIGN) == X_SIGN)
		v_x = v_x | 0xFFFFFF00;

	*xi += (int) v_x;

	if(*xi < 0)
		*xi = 0;

	if(*xi > (h_res - 20))
		*xi = (h_res - 20);

	if((packet[0] & Y_SIGN) == Y_SIGN)
		v_y = v_y | 0xFFFFFF00;

	*yi -= (char) v_y;

	if(*yi < 0)
		*yi = 0;

	if(*yi > (v_res - 35))
		*yi = (v_res  - 35);
}

int mouse_subscribe(void) //Subscribes to mouse interrupts in exclusive mode
{
	int original_m_hook_id = g_m_hook_id;

	if(sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &g_m_hook_id) != 0) //IRQ_EXCLUSIVE is used to "disable" Minix's default IH
	{
		printf("Couldn't subscribe\n");
		return 1;
	}

	if(sys_irqenable(&g_m_hook_id) != 0)
		return 1;

	return BIT(original_m_hook_id);
}

int mouse_unsubscribe() //Unsubscribes mouse interrupts
{
	if(sys_irqdisable(&g_m_hook_id) != 0)
		return 1;

	if(sys_irqrmpolicy(&g_m_hook_id) != 0)
		return 1;

		return 0;
}

void mouse_handler()
{
	unsigned long stat_byte, packet_byte;

	do
	{
		if(sys_inb(STAT_REG, &stat_byte) != 0) //Reads from status register
			return;

		if((stat_byte & OBF) != OBF)
			tickdelay(micros_to_ticks(DELAY_US));

	}while((stat_byte & OBF) != OBF); //Reads the out_buf


	if((stat_byte & PARITY) == PARITY) //Checks for parity error
		return;


	if((stat_byte & TIMEOUT) == TIMEOUT) //Check for timeout error
		return;


	if(sys_inb(OUT_BUF, &packet_byte) != 0) //Reads packet byte from out_buf
			return;


	if(((packet_byte & BIT(3)) == 0) && g_counter == 0) //If bit 3 of the first byte is not set ...
		return;
	else
	{
		g_packet[g_counter] = packet_byte;
		g_counter++;
	}

	if(g_counter == 3)
		g_counter = 0;
}

int write_mouse(unsigned long arg)
{
	unsigned long ack_byte, status_byte;

	do
	{
		if(sys_inb(STAT_REG, &status_byte) != 0)
			{
				printf("Couldn't read status register in write mouse\n");
				return 1;
			}
	}
	while((status_byte & IBF) == IBF); //Checks if In_Buf is full

	sys_outb(STAT_REG, WRITE_TO_MOUSE);
	sys_outb(IN_BUF, arg);

	tickdelay(micros_to_ticks(DELAY_US));

	do
	{
		if(sys_inb(STAT_REG, &status_byte) != 0)
		{
			printf("Couldn't read status register in write mouse\n");
			return 1;
		}

	}while((status_byte & OBF) != OBF);


	if(sys_inb(OUT_BUF, &ack_byte))
	{
		printf("Error in reading OUT_BUF in write_mouse\n");
		return 1;
	}

	return ack_byte;
}
