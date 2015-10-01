/****************************************************************************
	Luka Penger 2014
	LED CUBE 8x8x8 Animations
	LPC17xx
	Version 4.0.0
****************************************************************************/
#ifndef __LED_CUBE_8x8x8_Animations_H 
#define __LED_CUBE_8x8x8_Animations_H

#include <LED_CUBE_8x8x8.h>
#include <LED_CUBE_8x8x8_Translation.h>
#include <LED_CUBE_8x8x8_Rotation.h>
#include <ctype.h>

#define DEF_RIGHT move_x_fwd( 0, 0, 7, 1); defender_pos += 0x10;
#define DEF_LEFT move_x_rev( 0, 0, 7, 1); defender_pos -= 0x10;
#define DEF_BACK move_z_fwd( 0, 0, 1, 7); defender_pos += 0x01;
#define DEF_FWD move_z_rev( 0, 0, 1, 7); defender_pos -= 0x01;

void LED_CUBE_Animation_Char (char ch, unsigned int z);
void LED_CUBE_Animation_String_to_front (char *string);

void LED_CUBE_Animation_Move_belt_left (char *belt);
void LED_CUBE_Animation_Show_belt (char *belt);
void LED_CUBE_Animation_String_belt (char *string);

void LED_CUBE_Animation_Cube_2_auto (void);
char LED_CUBE_Animations_Cube2_move_y_fwd (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z);
char LED_CUBE_Animations_Cube2_move_y_rev (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z);
char LED_CUBE_Animations_Cube2_move_x_fwd (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z);
char LED_CUBE_Animations_Cube2_move_x_rev (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z);
char LED_CUBE_Animations_Cube2_move_z_fwd (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z);
char LED_CUBE_Animations_Cube2_move_z_rev (char cube2[4][4], uint8_t y, uint8_t x, uint8_t z);
void LED_CUBE_Animations_Cube_2_auto_show (char cube2[4][4]);

void LED_CUBE_Animations_wipe (void);
void LED_CUBE_Animations_explosion (void);
void LED_CUBE_Animations_Cubes_4 (void);
void LED_CUBE_Animations_Cubes_2 (void);
void LED_CUBE_Animations_Cube_stars (void);
void LED_CUBE_Animations_Cube_Outline (void);

#define WAVES_DELAY 60
#define WAVES_DEPTH 0xFF
void LED_CUBE_Animations_Cube_waves (void);

#define SONIC_DELAY 80
void LED_CUBE_Animations_Cube_sonic (void);

#define OUT_SHRINK_DELAY 140
void LED_CUBE_Animtions_Outline_shrink (void);

#define SHOW_BELT_DELAY 100
void LED_CUBE_Animations_Show_belt (char *belt);

#define INVADERS_DELAY 60
void LED_CUBE_Animations_Cube_invaders (void);

#define BELT_WIPE_DELAY 50
void LED_CUBE_Animations_Cube_belt_wipe (void);

#define BLOCK_WIPE_DELAY 50
void LED_CUBE_Animations_Cube_block_wipe (void);

#define STRIPES_DELAY 60
void LED_CUBE_Animations_Cube_stripes (void);

#endif /* end __LED_CUBE_8x8x8_Animations_H */
/**************************************************************************
                            End Of File
***************************************************************************/
