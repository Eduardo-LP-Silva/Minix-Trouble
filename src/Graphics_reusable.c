#include <minix/syslib.h>
#include <minix/drivers.h>
#include <minix/com.h>
#include <minix/sysutil.h>
#include <minix/driver.h>
#include <machine/int86.h>
#include "GPU.h"
#include "Graphics_reusable.h"

void set_mode(unsigned short mode)
{
	struct reg86u r;

	r.u.b.ah = VBE_FUNC;
	r.u.b.al = SET_VBE_MODE;
	r.u.w.bx = LINEAR_FRAME | mode;
	r.u.b.intno = BIOS_VID;

	sys_int86(&r);
}
