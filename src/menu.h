#ifndef __MENU_H
#define __MENU_H

/** @defgroup menu menu
 * @{
 *
 * Functions related to the different game menus
 */

#include "Bitmap.h"
/**
 * @brief Draws the Main timer_unsubscribe_int
 * @param bitmaps_MainMenu pointer to the array containing Bitmap* type elements, necessary to draw the main menu screen
 */
void draw_menu(Bitmap *bitmaps_MainMenu[]);

/**
 * @brief Creates an array of pointers to the bitmaps necessary to the main menu
 * @param bitmaps_MainMenu pointer to the array containing Bitmap* type elements, necessary to draw the main menu screen
 */
void create_bitmaps_MainMenu(Bitmap* bitmaps_MainMenu[]);

/**
 * @brief Creates an array of pointers to the bitmaps necessary to the game
 * @param bitmaps_game pointer to the array containing Bitmap* type elements, necessary to draw the game screen
 */
void create_bitmaps_game(Bitmap *bitmaps_game[]);

/**
 * @brief Creates an array of pointers to the bitmaps necessary to the end screen
 * @param bitmaps_endScreen pointer to the array containing Bitmap* type elements, necessary to draw the end screen
 */
void create_bitmaps_endScreen(Bitmap* bitmaps_endScreen[]);

#endif
