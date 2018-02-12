#ifndef __SERVER_H
#define __SERVER_H

/** @defgroup Server server
 * @{
 *
 * Functions related to the servers management
 */

/** @name Server */
/**@{
 *
 * Game prop Server
 */

typedef struct {
    short x_coord; /**< @brief x coordinate of the server */
    short y_coord; /**< @brief y coordinate of the server */
    short width;   /**< @brief width of the server */
    short height;  /**< @brief height of the server */
    int broken_flag; /**< @brief integer number that indicates whether the server is broken or not */
} Server;

/**
 * @brief Constructs a new Server, allocating memory with malloc for it
 * @param  x_pos x coordinate of the server's upper left corner
 * @param  y_pos y coordinate of the server's upper left corner
 * @return       returns the a pointer to the new created server
 */
Server *new_server(short x_pos, short y_pos);

/**
 * @brief Frees the memory ocupied by the server passed as argument
 * @param s server that will be erased
 */
void delete_server(Server* s);

/**
 * @brief Creates a server of Server* type elements, corresponding to the servers present in the game
 * @param server_array [description]
 */
void create_serverArray (Server *server_array[]);

/**
 * @brief Breaks a server from all the servers present in game
 * @param  server_array pointer to an array of Server* type elements, that are present in the game
 * @param  n_servers    [number of servers present in the game (size of the server_array)
 * @return              returns 1 if the game is over (if all the servers are broken), 0 otherwise
 */
int break_server(Server *server_array[], int n_servers);

/**
 * @brief
 * @param  server_array pointer to an array of Server* type elements, that are present in the game
 * @param  n_servers    number of servers present in the game (size of the server_array)
 * @param  index        variable where if index of the last good server, if it is the case where there is only 1 good server left
 * @return              returns 1 if there is only one good server, 0 otherwise
 */
int check_nGoodServers(Server *server_array[], int n_servers, int *index);

/**
 * @brief Generates a random number from 0 to the max argument
 * @param  max maximum number that can be generated
 * @return     returns the number generated
 */
long random_at_most(unsigned long max);

/**
 * @brief Fixes a specific broken server
 * @param  server_array pointer to an array of Server* type elements, that are present in the game
 * @param  n_servers    number of servers present in the game (size of the server_array)
 * @param  serverID     index of the server, corresponding to the server_array array,  that will be fixed
 * @param  score        score of the player, passed by reference
 * @return              returns 0 uppon success, non-zero otherwise
 */
int fix_server (Server* server_array[], int n_servers, int serverID, int *score);

#endif
