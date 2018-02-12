#ifndef __TIMER_KBD_REUSABLE_H
#define __TIMER_KBD_REUSABLE_H

/** @defgroup timerKBDreusable timerKBDreusable
 * @{
 *
 * Previous lab functions related to the keyboard and the timer
 */

//Keyboard
extern unsigned long g_key_code; /**<@brief key code received from the keyboard */

/**
 * @brief Keyboard interrrupts handler in C
 */
void C_kbd_handler();

/**
 * @brief Subscribes to the keyboard interrupts
 * @return  returns 0 upon success, non-zero otherwise
 */
int kbc_subscribe(void);

/**
 * @brief Unsubscribes the keyboard interrupts
 * @return returns 0 upon success, non-zero otherwise
 */
int kbc_unsubscribe();

//Timer
extern unsigned long g_timer_cnt;

/**
 * @brief Timer interrupts handler in C
 */
void timer_int_handler();

/**
 * @brief Subscribes to the TIMER 0 interrupts
 * @return  returns 0 upon success, non-zero otherwise
 */
int timer_subscribe_int(void);

/**
 * @brief Unsubscribes to the TIMER 0 interrupts
 * @return returns 0 upon success, non-zero otherwise
 */
int timer_unsubscribe_int();

#endif
