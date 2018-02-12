#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include <machine/int86.h>

#include "menu.h"

void draw_menu(Bitmap *bitmaps_MainMenu[])
{
	drawBitmap_pixels(bitmaps_MainMenu[0], 0, 0, ALIGN_LEFT);
  drawBitmap_pixels(bitmaps_MainMenu[1], 10, 200, ALIGN_LEFT);
	drawBitmap_pixels(bitmaps_MainMenu[2], 512, 10, ALIGN_CENTER);
	drawBitmap_pixels(bitmaps_MainMenu[3], 512, 300, ALIGN_CENTER);
	drawBitmap_pixels(bitmaps_MainMenu[4], 512, 400, ALIGN_CENTER);
}

void create_bitmaps_MainMenu(Bitmap* bitmaps_MainMenu[]) {

	Bitmap *background = loadBitmap("/home/lcom/svn/proj/Bitmaps/floor_mosaic.bmp");
	Bitmap *character_full = loadBitmap("/home/lcom/svn/proj/Bitmaps/Character_full.bmp");
	Bitmap *title = loadBitmap("/home/lcom/svn/proj/Bitmaps/title.bmp");
	Bitmap *cursor = loadBitmap("/home/lcom/svn/proj/Bitmaps/Cursor.bmp");
	Bitmap *start = loadBitmap("/home/lcom/svn/proj/Bitmaps/Start.bmp");
	Bitmap *exitb = loadBitmap("/home/lcom/svn/proj/Bitmaps/exit.bmp");

	bitmaps_MainMenu[0] = background;
	bitmaps_MainMenu[1] = character_full;
	bitmaps_MainMenu[2] = title;
	bitmaps_MainMenu[3] = start;
	bitmaps_MainMenu[4] = exitb;
	bitmaps_MainMenu[5] = cursor;
}

void create_bitmaps_game(Bitmap *bitmaps_game[]) {
	Bitmap *good_server = loadBitmap("/home/lcom/svn/proj/Bitmaps/good_server.bmp");
	Bitmap *character = loadBitmap("/home/lcom/svn/proj/Bitmaps/main_character_2.bmp");
	Bitmap *broken_server = loadBitmap("/home/lcom/svn/proj/Bitmaps/broken_server.bmp");
	Bitmap *floor = loadBitmap("/home/lcom/svn/proj/Bitmaps/floor_mosaic.bmp");

	bitmaps_game[0] = floor;
	bitmaps_game[1] = character;;
	bitmaps_game[2] = good_server;
	bitmaps_game[3] = broken_server;
}

void create_bitmaps_endScreen(Bitmap* bitmaps_endScreen[]) {

	Bitmap *game_over = loadBitmap("/home/lcom/svn/proj/Bitmaps/game_over_1.bmp");
	Bitmap *dig_0 = loadBitmap("/home/lcom/svn/proj/Bitmaps/0.bmp");
	Bitmap *dig_1 = loadBitmap("/home/lcom/svn/proj/Bitmaps/1.bmp");
	Bitmap *dig_2 = loadBitmap("/home/lcom/svn/proj/Bitmaps/2.bmp");
	Bitmap *dig_3 = loadBitmap("/home/lcom/svn/proj/Bitmaps/3.bmp");
	Bitmap *dig_4 = loadBitmap("/home/lcom/svn/proj/Bitmaps/4.bmp");
	Bitmap *dig_5 = loadBitmap("/home/lcom/svn/proj/Bitmaps/5.bmp");
	Bitmap *dig_6 = loadBitmap("/home/lcom/svn/proj/Bitmaps/6.bmp");
	Bitmap *dig_7 = loadBitmap("/home/lcom/svn/proj/Bitmaps/7.bmp");
	Bitmap *dig_8 = loadBitmap("/home/lcom/svn/proj/Bitmaps/8.bmp");
	Bitmap *dig_9 = loadBitmap("/home/lcom/svn/proj/Bitmaps/9.bmp");

	bitmaps_endScreen[0] = dig_0;
	bitmaps_endScreen[1] = dig_1;
	bitmaps_endScreen[2] = dig_2;
	bitmaps_endScreen[3] = dig_3;
	bitmaps_endScreen[4] = dig_4;
	bitmaps_endScreen[5] = dig_5;
	bitmaps_endScreen[6] = dig_6;
	bitmaps_endScreen[7] = dig_7;
	bitmaps_endScreen[8] = dig_8;
	bitmaps_endScreen[9] = dig_9;
	bitmaps_endScreen[10] = game_over;

}
