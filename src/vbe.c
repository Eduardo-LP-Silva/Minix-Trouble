#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>

#include "vbe.h"
#include "lmlib.h"
#include "GPU.h"

#define LINEAR_MODEL_BIT 14

#define INFOBLOCK_SIZE		sizeof(vbe_mode_info_t)
#define INFO_CONTROL_SIZE	sizeof(vbe_control_info_t)
#define PB2BASE(x) (((x) >> 4) & 0x0F000)
#define PB2OFF(x) ((x) & 0x0FFFF)

int vbe_get_mode_info(unsigned short mode, vbe_mode_info_t *vmi_p) {

	mmap_t map;
	struct reg86u r;

	if(lm_init() == NULL)
		return 1;


	lm_alloc(INFOBLOCK_SIZE, &map);

	r.u.b.ah = VBE_FUNC;
	r.u.b.al = MOD_INFO;
	r.u.w.es = PB2BASE(map.phys);
	r.u.w.di = PB2OFF(map.phys);
	r.u.w.cx = mode;
	r.u.b.intno = BIOS_VID;

	if( sys_int86(&r) != OK )
		return 1;


	*vmi_p = *(vbe_mode_info_t*) map.virtual;

	lm_free(&map);

  return 0;
}

int vbe_get_control_info(vbe_control_info_t *vbemi_p){

	mmap_t map;
	struct reg86u r;

	if(lm_init() == NULL)
		return 1;


	lm_alloc(INFO_CONTROL_SIZE, &map);

	r.u.b.ah = VBE_FUNC;
	r.u.b.al = VBE_CONTROL_INFO;
	r.u.w.es = PB2BASE(map.phys);
	r.u.w.di = PB2OFF(map.phys);
	r.u.b.intno = BIOS_VID;

	if( sys_int86(&r) != OK )
		return 1;

	*vbemi_p = *(vbe_control_info_t*) map.virtual;

	lm_free(&map);


	return 0;
}


