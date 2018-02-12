#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include "i8042.h"
#include "i8254.h"
#include "timer_kbd_reusable.h"

//Keyboard

int g_k_hook_id = 1, g_t_hook_id = 0;

void C_kbd_handler() //C Keyboard Interrupt Handler
{
	unsigned long stat_byte;

	if(sys_inb(STAT_REG, &stat_byte) != 0) //Reads from status register
		return;

	while((stat_byte & OBF) != 0x01) //Only reads from OF if it has actual data to read
	{
		if(sys_inb(STAT_REG, &stat_byte) != 0)
			return;

		if(stat_byte & PARITY) //Checks for parity error
			return;


		if(stat_byte & TIMEOUT) //Check for timeout error
			return;

		if(stat_byte & AUX) //Checks for mouse data
			return;
	}

	if(sys_inb(OUT_BUF, &g_key_code) != 0) //Reads scancode
		return;
}

int kbc_subscribe(void)
{
	int original_k_hook_id = g_k_hook_id;

	 if(sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &g_k_hook_id) != 0) //IRQ_EXCLUSIVE is used to "disable" Minix's default IH
		return 1;

	return BIT(original_k_hook_id);
}

int kbc_unsubscribe()
{
	if(sys_irqrmpolicy(&g_k_hook_id) != 0)
		return 1;

	return 0;
}

//Timer

int timer_subscribe_int(void)
{
	int original_t_hook_id = g_t_hook_id;

	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &g_t_hook_id) != 0)
		return -1;


	if(sys_irqenable(&g_t_hook_id) != 0)
		return -1;

	return BIT(original_t_hook_id);
}

void timer_int_handler()
{
	g_timer_cnt++;
}

int timer_unsubscribe_int()
{
	if(sys_irqrmpolicy(&g_t_hook_id) != 0)
		return 1;

	return 0;
}
