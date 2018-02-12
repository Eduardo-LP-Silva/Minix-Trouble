#ifndef __VIDEO_GR_H
#define __VIDEO_GR_H

/** @defgroup video_gr video_gr
 * @{
 *
 * Functions for outputing data to screen in graphics mode
 */

/**
 * @brief Initializes the video module in graphics mode
 *
 * Uses the VBE INT 0x10 interface to set the desired
 *  graphics mode, maps VRAM to the process' address space and
 *  initializes static global variables with the resolution of the screen,
 *  and the number of colors
 *
 * @param mode 16-bit VBE mode to set
 * @return Virtual address VRAM was mapped to. NULL, upon failure.
 */
void *vg_init(unsigned short mode);

 /**
 * @brief Returns to default Minix 3 text mode (0x03: 25 x 80, 16 colors)
 *
 * @return 0 upon success, non-zero upon failure
 */
int vg_exit(void);

/**
 * @brief gets the horizontal resolution of the screen
 * @return returns the horizontal resolution of the screen
 */
unsigned get_hres();

/**
 * @brief gets the vertical resolution of the screen
 * @return returns the vertical resolution of the screen
 */
unsigned get_vres();

/**
 * @brief gets the bits_per_pixel variable
 * @return returns the value of the bits_per_pixel variable
 */
unsigned get_bitpp();

/**
 * @brief gets the vram buffer pointer
 * @return returns the vram buffer pointer
 */
char* get_video_mem();

/**
 * @brief gets the auxiliar buffer pointer
 * @return returns the auxiliar buffer pointer
 */
char* get_aux_mem();

/**
 * @brief copies what is in the auxiliar buffer to the vram buffer
 */
void buffer_cpy();

 /** @} end of video_gr */

#endif /* __VIDEO_GR_H */
