#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include <machine/int86.h>
#include "movement.h"
#include "MACROS.h"
#include "i8042.h"
#include "video_gr.h"

void draw_map(Bitmap *bitmaps_game[], Server* server_array[], int n_servers)
{
	int i;

	drawBitmap(bitmaps_game[0], 0, 0, ALIGN_LEFT);

	for(i = 0; i < n_servers; i++) {

		if(server_array[i]->broken_flag == 1)
			drawBitmap(bitmaps_game[3], server_array[i]->x_coord, server_array[i]->y_coord, ALIGN_LEFT);
		else{
			drawBitmap(bitmaps_game[2], server_array[i]->x_coord, server_array[i]->y_coord, ALIGN_LEFT);
		}
	}
}

int colision_with_server(Server* server, short ch_x, short ch_y) {

	if(
		(ch_x >= server->x_coord) && (ch_x <= server->x_coord + server->width)
			&& (ch_y >= server->y_coord) && (ch_y <= server->y_coord + server->height)
	)
	{
		return 1;
	}

	return 0;
}

int check_colision(short ch_x, short ch_y, Server* server_array[], int n_servers) {

	int i = 0;

	for(i = 0; i < n_servers; i++) {

		if(colision_with_server(server_array[i], ch_x, ch_y) == 1)
			return i;

	}
	return -1;

}

void move(short *ch_x, short *ch_y, Bitmap* bitmap_array[], Server* server_array[], int n_servers)
{
	switch(g_key_code)
	{
	case W_SC:
		draw_map(bitmap_array, server_array, n_servers);
		*ch_y -= 10;
		drawBitmap_pixels(bitmap_array[1], *ch_x, *ch_y, ALIGN_LEFT);
		break;

	case S_SC:
		draw_map(bitmap_array, server_array, n_servers);
		*ch_y += 10;
		drawBitmap_pixels(bitmap_array[1], *ch_x, *ch_y, ALIGN_LEFT);
		break;

	case A_SC:
		draw_map(bitmap_array, server_array, n_servers);
		*ch_x -= 10;
		drawBitmap_pixels(bitmap_array[1], *ch_x, *ch_y, ALIGN_LEFT);
		break;

	case D_SC:
		draw_map(bitmap_array, server_array, n_servers);
		*ch_x += 10;
		drawBitmap_pixels(bitmap_array[1], *ch_x, *ch_y, ALIGN_LEFT);
		break;

	default:
		break;
   }
}
