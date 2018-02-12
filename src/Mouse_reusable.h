#ifndef __MOUSE_REUSABLE_H
#define __MOUSE_REUSABLE_H

/** @defgroup MouseReusable MouseReusable
 * @{
 *
 * Previous lab functions related to the mouse
 */

#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include "i8042.h"
#include "i8254.h"
#include "PS2.h"
#include "Bitmap.h"
#include "timer_kbd_reusable.h"
#include "video_gr.h"

unsigned long g_counter;       /**<@brief number of packets read */
unsigned long g_packet[3];     /**<@brief array that stores the packets received from the mouse */

/**
 * @brief Mouse interrupt handler in assembly
 */
void M_ASM_IH();

/**
 * @brief updates the mouse cursor coordinates if an interrupt is identified
 * @param packet packets received from the mouse
 * @param xi     x coordinate of the upper left corner of the mouse
 * @param yi     y coordinate of the upper left corner of the mosue
 */
void update_coords(unsigned long packet[], int *xi, int *yi);

/**
 * @brief Subscribes to the mouse interrupts
 * @return  returns 0 upon success, non-zero otherwise
 */
int mouse_subscribe(void);

/**
 * @brief Unsubscribes to the mouse interrupts
 * @return  returns 0 upon success, non-zero otherwise
 */
int mouse_unsubscribe();

/**
 * @brief Mouse interrupt handler in C
 */
void mouse_handler();

/**
 * @brief Writes a command to the mouse
 * @param  arg Command to be writen to the mouse
 * @return     Returns 0 upon success, non-zero otherwise
 */
int write_mouse(unsigned long arg);


#endif
