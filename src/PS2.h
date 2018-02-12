#ifndef __PS2_H
#define __PS2_H

/** @defgroup PS2 PS2
 * @{
 *
 * Constants related to the mouse
 */

#define BIT(n) (0x01<<(n))
#define MOUSE_IRQ 12
#define EN_STREAM_M 0xEA
#define WRITE_TO_MOUSE 0xD4
#define EN_DATA_REP 0xF4
#define DIS_DATA_REP 0xF5
#define SET_REMOTE 0xF0
#define READ_DATA_M 0xEB

//Packets

#define LB BIT(0)
#define RB BIT(1)
#define MB BIT(2)
#define X_SIGN BIT(4)
#define Y_SIGN BIT(5)
#define X_OVF BIT(6)
#define Y_OVF BIT(7)

#endif
