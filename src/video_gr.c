#include <minix/syslib.h>
#include <minix/drivers.h>
#include <machine/int86.h>
#include <sys/mman.h>
#include <sys/types.h>

#include "vbe.h"
#include "Graphics_reusable.h"

/* Constants for VBE 0x105 mode */

/* The physical address may vary from VM to VM.
 * At one time it was 0xD0000000
 *  #define VRAM_PHYS_ADDR    0xD0000000
 * Currently on lab B107 is 0xF0000000
 * Better run my version of lab5 as follows:
 *     service run `pwd`/lab5 -args "mode 0x105"
 */
#define VRAM_PHYS_ADDR	0xE0000000
#define H_RES         1024
#define V_RES		  768
#define BITS_PER_PIXEL	  8

/* Private global variables */

static char *video_mem;		/* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;		/* Horizontal screen resolution in pixels */
static unsigned v_res;		/* Vertical screen resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */
static char *aux_mem;

unsigned get_hres()
{
	return h_res;
}

unsigned get_vres()
{
	return v_res;
}

unsigned get_bitpp()
{
	return bits_per_pixel;
}

char* get_video_mem()
{
	return video_mem;
}

char* get_aux_mem()
{
	return aux_mem;
}

void buffer_cpy()
{
    memcpy(video_mem, aux_mem, h_res * v_res * bits_per_pixel / 8);
}

void *vg_init(unsigned short mode)
{

	int r;
	struct mem_range mr;
	unsigned int vram_size;
	vbe_mode_info_t vmi_p;
	unsigned bytes_per_pixel;

	set_mode(mode);

	if(vbe_get_mode_info(mode, &vmi_p) != 0){
		printf("\terror: vbe_get_mode_info failure");
		return NULL;
	}

	bits_per_pixel = vmi_p.BitsPerPixel;
	h_res = vmi_p.XResolution;
	v_res = vmi_p.YResolution;

	if (bits_per_pixel/8 <= 0)
		bytes_per_pixel = 1;
	else
		bytes_per_pixel = bits_per_pixel/8;

	vram_size = h_res * v_res * bytes_per_pixel;

	/* Allow memory mapping */

	mr.mr_base = (phys_bytes) vmi_p.PhysBasePtr;
	mr.mr_limit = mr.mr_base + vram_size;

	if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
	   panic("sys_privctl (ADD_MEM) failed: %d\n", r);
	/* Map memory */

	video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

	if(video_mem == MAP_FAILED)
	   panic("couldn't map video memory");

	aux_mem = malloc(vram_size);

	return (void*) video_mem;

}

int vg_exit()
{
  struct reg86u reg86;

  reg86.u.b.intno = 0x10; /* BIOS video services */

  reg86.u.b.ah = 0x00;    /* Set Video Mode function */
  reg86.u.b.al = 0x03;    /* 80x25 text mode*/

  if( sys_int86(&reg86) != OK ) {
      printf("\tvg_exit(): sys_int86() failed \n");
      return 1;
  } else
      return 0;
}
