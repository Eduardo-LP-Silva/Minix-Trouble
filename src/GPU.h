#ifndef __GPU_H
#define __GPU_H

/** @defgroup GPU GPU
 * @{
 *
 * Constants related to GPU functions
 */

#define BIT(n) (0x01<<(n))
#define VBE_FUNC 0x4F
#define MOD_INFO 0x01
#define SET_VBE_MODE 0x02
#define LINEAR_FRAME BIT(14)
#define BIOS_VID 0x10
#define TEXT_MODE 0x03
#define VBE_CONTROL_INFO 0x00
#define MEMORY_BLOCK 64  //Kb of storage

#endif
