#ifndef __i8042_H
#define __i8042_H

/** @defgroup i8042 i8042
 * @{
 *
 * Constants related to the keyboard
 */

//Keyboard

#define KBD_IRQ 1
#define BIT(n) (0x01<<(n))
#define DELAY_US 20000
#define ESC_BR 0x81
#define W_SC 0x11
#define A_SC 0x1E
#define S_SC 0x1F
#define D_SC 0x20
#define E_SC 0x12


//KBC

#define OUT_BUF 0x60
#define IN_BUF 0x60

//Keyboard Command Bytes

#define READ_CMD_B 0x20
#define WRITE_CMD_B 0x60
#define EN_KBD_OBF BIT(0) //Enables interrupts on OBF, from keyboard

//Stauts Register

#define STAT_REG 0x64
#define PARITY BIT(7)
#define TIMEOUT BIT(6)
#define AUX BIT(5)
#define IBF BIT(1)
#define OBF BIT(0)

#endif
