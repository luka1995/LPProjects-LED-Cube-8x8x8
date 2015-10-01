/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8 Translation
	LPC17xx
	Version 4.0.0
****************************************************************************/
#ifndef __LED_CUBE_8x8x8_Translation_H 
#define __LED_CUBE_8x8x8_Translation_H

#include <LED_CUBE_8x8x8.h>

void move_z_fwd (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void move_z_rev (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void move_y_fwd (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void move_y_rev (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void move_x_fwd (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void move_x_rev (uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

#endif /* end __LED_CUBE_8x8x8_Translation_H */
/**************************************************************************
                            End Of File
***************************************************************************/
