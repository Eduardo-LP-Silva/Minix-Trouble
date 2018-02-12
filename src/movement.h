#ifndef __MOVEMENT_H
#define __MOVEMENT_H

/** @defgroup movement movement
 * @{
 *
 * Functions related to the movement of the character and colisions
 */

#include "server.h"
#include "Bitmap.h"

extern unsigned long g_key_code; /**<@brief key code received from the keyboard */

/**
 * @brief Recognizes the movement keys the user presses
 * @param ch_x         x coordinate of the character
 * @param ch_y         y coordinate of the character
 * @param bitmap_array pointer to an array of Bitmap* type elements, that are used in the game
 * @param server_array pointer to an array of Server* type elements, that are present in the game
 * @param n_servers    number of servers present in the game (size of the server_array)
 */
void move(short *ch_x, short *ch_y, Bitmap* bitmap_array[], Server* server_array[], int n_servers);

/**
 * @brief  Verifies if the character center is in colision with any server
 * @param  ch_x         x coordinate of the character
 * @param  ch_y         y coordinate of the character
 * @param  server_array pointer to an array of Server* type elements, that are present in the game
 * @param  n_servers    number of servers present in the game (size of the server_array)
 * @return              If the character is in colision with a server, returns the index of that server corresponding to server_array, -1 otherwise
 */
int check_colision(short ch_x, short ch_y, Server* server_array[], int n_servers);

/**
 * @brief Verifies if the character is in colision with one server
 * @param  server pointer to the server with which colision is being verifie
 * @param  ch_x   x coordinate of the character
 * @param  ch_y   y coordinate of the character
 * @return        returns 1 upon colision, 0 otherwise
 */
int colision_with_server(Server* server, short ch_x, short ch_y);
/**
 * @brief Draws the map of the game
 * @param bitmap_array pointer to an array of Bitmap* type elements, that are used in the game
 * @param server_array pointer to an array of Server* type elements, that are present in the game
 * @param n_servers    number of servers present in the game (size of the server_array)
 */
void draw_map(Bitmap *bitmaps_game[], Server* server_array[], int n_servers);
#endif
