/****************************************************************************
	Luka Penger 2013
	I2C
	LPC17xx
****************************************************************************/
#ifndef __I2C_H 
#define __I2C_H

#include <LPC17xx.h>
#include "type.h"

#define I2C_PORT_NUM					3

static LPC_I2C_TypeDef (* const LPC_I2C[I2C_PORT_NUM]) = { LPC_I2C0, LPC_I2C1, LPC_I2C2 };

#define I2C_BUFSIZE           64
#define I2C_MAX_TIMEOUT       0x00FFFFFF

#define I2C_MASTER           	0x01
#define I2C_SLAVE            	0x02

#define I2C_READ_BIT          0x01

#define I2C_IDLE              0
#define I2C_STARTED           1
#define I2C_RESTARTED         2
#define I2C_REPEATED_START    3
#define I2C_DATA_ACK          4
#define I2C_DATA_NACK         5
#define I2C_BUSY              6
#define I2C_NO_DATA           7
#define I2C_NACK_ON_ADDRESS   8
#define I2C_NACK_ON_DATA      9
#define I2C_ARBITRATION_LOST  10
#define I2C_TIME_OUT          11
#define I2C_OK                12

#define I2CONSET_I2EN       (0x1<<6)  /* I2C Control Set Register */
#define I2CONSET_AA         (0x1<<2)
#define I2CONSET_SI         (0x1<<3)
#define I2CONSET_STO        (0x1<<4)
#define I2CONSET_STA        (0x1<<5)

#define I2CONCLR_AAC        (0x1<<2)  /* I2C Control clear Register */
#define I2CONCLR_SIC        (0x1<<3)
#define I2CONCLR_STAC       (0x1<<5)
#define I2CONCLR_I2ENC      (0x1<<6)

#define I2DAT_I2C			0x00000000  /* I2C Data Reg */
#define I2ADR_I2C			0x00000000  /* I2C Slave Address Reg */
#define I2SCLH_SCLH			0x00000080  /* I2C SCL Duty Cycle High Reg */
#define I2SCLL_SCLL			0x00000080  /* I2C SCL Duty Cycle Low Reg */
#define I2SCLH_HS_SCLH		0x00000008  /* Fast Plus I2C SCL Duty Cycle High Reg */
#define I2SCLL_HS_SCLL		0x00000008  /* Fast Plus I2C SCL Duty Cycle Low Reg */

void I2C0_Init(BOOL fastMode);
void I2C1_Init(BOOL pinsSelect);
void I2C2_Init(void);
unsigned int I2C_Start(char portNum);
unsigned int I2C_Stop(char portNum);
unsigned int I2C_Engine(char portNum);
extern void I2C0_IRQHandler(void);
extern void I2C1_IRQHandler(void);
extern void I2C2_IRQHandler(void);

#endif /* end __I2C_H */
/**************************************************************************
                            End Of File
**************************************************************************/
