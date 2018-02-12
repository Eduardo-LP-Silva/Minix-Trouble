#ifndef __MAIN_H
#define __MAIN_H

/** @defgroup main main
 * @{
 *
 * Main Functions of the game
 */

#include "time.h"
#include "menu.h"
#include "vbe.h"
#include "video_gr.h"
#include "movement.h"
#include "timer_kbd_reusable.h"
#include "Graphics_reusable.h"
#include "lmlib.h"
#include "Mouse_reusable.h"
#include "GPU.h"
#include "i8042.h"
#include "i8254.h"
#include "PS2.h"
#include "MACROS.h"

/** @name state_t */
/**@{
 *
 * Defines the diferent states the game maight be in
 */
typedef enum {init, play, game_over_s, end} state_t;

/** @name ev_type_t */
/**@{
 *
 * Identifies what will be the next event after a determined state
 */
typedef enum {start_b, exit_b, null, esc_press, lost_game} ev_type_t;

/** @name State_Machine */
/**@{
 *
 * 	Manages the state in which the game is
 */

typedef struct
{
	state_t current_state; /**< @brief current state of the game */
	ev_type_t next_event; /**< @brief defines the next event */
} State_Machine;

/**
 * @brief Creates the Main Menu, from which the game can be started
 *
 * Using the mouse and the timer, it allows the user to either start the game, or exit the program.
 * After the user chooses one of the options, it changes the current_state of the state machine, and procedes with the execution.
 *
 * @param st state machine that manages the state in which the game can be
 */
void Main_Menu(State_Machine *st);

/**
 * @brief	Manages the state in which the game is
 *
 * Implemented by us, this state machine allows the management of the state of the game eficiently, using a switch case.
 *
 * @param st state machine that manages the state in which the game can be
 */
void state_machine(State_Machine *st);

/**
 * @brief Cycle that runs as the user plays the game
 *
 * This function starts by subscribing to the timer and keyboard interrupts and by creating the array of bitmaps that will be used by the different sub-functions.
 *
 * Then a while cycle will "run" the game, by breaking the servers, one by one, and allowing a character to move and keep fixing those servers, until the user no longer
 * can keep at least one server functioning. If the character center is in colision with any of the broken servers and the user presses the E, then the server where
 * the colision is identified is fixed.
 *
 * This cycle ends when the user presses the ESC key or when he loses the game, because both these actions change the current_state and the next_event
 * of the state machine st.
 * The function cycle only ends after all the unsubscribing and buff clearing is done, and returns the score the player achieved.
 *
 * @param  st state machine that manages the state in which the game can be
 * @return    Returns the score the player achieved
 */
int cycle(State_Machine *st);

/**
 * @brief	Creates the end game screen (when the game is over)
 *
 * This function is called when either when the player loses the game or when the player simply quits the game by pressing the ESC key.
 * It prints on the screen the score the player achieved (using print_score function).
 * The user can simply press the ESC key to return to the main menu, and either leave or start a new game.
 *
 * @param score integer value representing the score the player achieved
 * @param st    state machine that manages the state in which the game can be
 */
void game_over(int score, State_Machine *st);

/**
 * @brief
 * @return returns the tick counter value
 */
unsigned long ASM_IH();
#endif
