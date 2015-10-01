/****************************************************************************
	Luka Penger 2013
	I2C
	LPC17xx
****************************************************************************/

#include "I2C.h"

volatile unsigned int I2C_MasterState[I2C_PORT_NUM] = {I2C_IDLE,I2C_IDLE,I2C_IDLE};
volatile unsigned int I2C_Timeout[I2C_PORT_NUM] = {0, 0, 0};

volatile unsigned char I2C_MasterBuffer[I2C_PORT_NUM][I2C_BUFSIZE];
volatile unsigned char I2C_SlaveBuffer[I2C_PORT_NUM][I2C_BUFSIZE];
volatile unsigned int I2C_Count[I2C_PORT_NUM] = {0, 0, 0};
volatile unsigned int I2C_ReadLength[I2C_PORT_NUM];
volatile unsigned int I2C_WriteLength[I2C_PORT_NUM];

volatile unsigned int RdIndex0 = 0, RdIndex1 = 0, RdIndex2 = 0;
volatile unsigned int WrIndex0 = 0, WrIndex1 = 0, WrIndex2 = 0;

/*****************************************************************************
** Function name:		I2C Init
**
** Descriptions:		Initialize I2C controller as a master
**
** parameters:			Fast mode enable/disable
** Returned value:	None
** 
*****************************************************************************/

void I2C0_Init(BOOL fastMode) {
	LPC_SC->PCONP |= (1 << 7);

	/* set PIO0.27 and PIO0.28 to I2C0 SDA and SCL */
	/* function to 01 on both SDA and SCL. */
	LPC_PINCON->PINSEL1 &= ~((0x03<<22)|(0x03<<24));
	LPC_PINCON->PINSEL1 |= ((0x01<<22)|(0x01<<24));	
 
	/*--- Clear flags ---*/
	LPC_I2C0->I2CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;    

	/*--- Reset registers ---*/
	if(fastMode)
	{
		LPC_PINCON->I2CPADCFG |= ((0x1<<0)|(0x1<<2));
		LPC_I2C0->I2SCLL   = I2SCLL_HS_SCLL;
		LPC_I2C0->I2SCLH   = I2SCLH_HS_SCLH;
	} else {
		LPC_PINCON->I2CPADCFG &= ~((0x1<<0)|(0x1<<2));
		LPC_I2C0->I2SCLL   = I2SCLL_SCLL;
		LPC_I2C0->I2SCLH   = I2SCLH_SCLH;
	}

	/* Install interrupt handler */
	NVIC_EnableIRQ(I2C0_IRQn);

	LPC_I2C0->I2CONSET = I2CONSET_I2EN;
}

void I2C1_Init(BOOL pinsSelect) {
	LPC_SC->PCONP |= (1 << 19);

	if(pinsSelect) {
		/* set PIO0.19 and PIO0.20 to I2C1 SDA and SCL */
		/* function to 11 on both SDA and SCL. */
		LPC_PINCON->PINSEL1 &= ~((0x3<<6)|(0x3<<8));
		LPC_PINCON->PINSEL1 |= ((0x3<<6)|(0x3<<8));
		LPC_PINCON->PINMODE1 &= ~((0x3<<6)|(0x3<<8));
		LPC_PINCON->PINMODE1 |= ((0x2<<6)|(0x2<<8));	/* No pull-up no pull-down */
		LPC_PINCON->PINMODE_OD0 |= ((0x1<<19)|(0x1<<20));		
	} else {
		/* set PIO0.0 and PIO0.1 to I2C1 SDA and SCL */
		/* function to 11 on both SDA and SCL. */
		LPC_PINCON->PINSEL0 &= ~((0x3<<0)|(0x3<<2));
		LPC_PINCON->PINSEL0 |= ((0x3<<0)|(0x3<<2));
		LPC_PINCON->PINMODE0 &= ~((0x3<<0)|(0x3<<2));
		LPC_PINCON->PINMODE0 |= ((0x2<<0)|(0x2<<2));		/* No pull-up no pull-down */
		LPC_PINCON->PINMODE_OD0 |= ((0x01<<0)|(0x1<<1));	/* Open drain */
	}
 
  /*--- Clear flags ---*/
  LPC_I2C1->I2CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;    

  /*--- Reset registers ---*/
  LPC_I2C1->I2SCLL   = I2SCLL_SCLL;
  LPC_I2C1->I2SCLH   = I2SCLH_SCLH;

  /* Install interrupt handler */
  NVIC_EnableIRQ(I2C1_IRQn);

  LPC_I2C1->I2CONSET = I2CONSET_I2EN;
}

void I2C2_Init(void) {
	LPC_SC->PCONP |= (1 << 26);

  /* set PIO0.10 and PIO0.11 to I2C2 SDA and SCL */
  /* function to 10 on both SDA and SCL. */
  LPC_PINCON->PINSEL0 &= ~((0x03<<20)|(0x03<<22));
  LPC_PINCON->PINSEL0 |= ((0x02<<20)|(0x02<<22));
  LPC_PINCON->PINMODE0 &= ~((0x03<<20)|(0x03<<22));
  LPC_PINCON->PINMODE0 |= ((0x02<<20)|(0x2<<22));	/* No pull-up no pull-down */
  LPC_PINCON->PINMODE_OD0 |= ((0x01<<10)|(0x1<<11));	
 
  /*--- Clear flags ---*/
  LPC_I2C2->I2CONCLR = I2CONCLR_AAC | I2CONCLR_SIC | I2CONCLR_STAC | I2CONCLR_I2ENC;    

  /*--- Reset registers ---*/
  LPC_I2C2->I2SCLL   = I2SCLL_SCLL;
  LPC_I2C2->I2SCLH   = I2SCLH_SCLH;

  /* Install interrupt handler */
  NVIC_EnableIRQ(I2C2_IRQn);

  LPC_I2C2->I2CONSET = I2CONSET_I2EN;
}

/*****************************************************************************
** Function name:		I2C	Start
**
** Descriptions:		Create I2C start condition, a timeout
**									value is set if the I2C never gets started,
**									and timed out. It's a fatal error. 
**
** parameters:			None
** Returned value:	True or False, return False if timed out
** 
*****************************************************************************/

unsigned int I2C_Start(char portNum) {
	unsigned int retVal = FALSE;
 
  I2C_Timeout[portNum] = 0;

	/*--- Issue a start condition ---*/
	LPC_I2C[portNum]->I2CONSET = I2CONSET_STA;	/* Set Start flag */
		
	/*--- Wait until START transmitted ---*/
	while(1)
	{
		if(I2C_MasterState[portNum] == I2C_STARTED)
		{
			retVal = TRUE;
			break;	
		}
		if(I2C_Timeout[portNum] >= I2C_MAX_TIMEOUT)
		{
			retVal = FALSE;
			break;
		}
		I2C_Timeout[portNum]++;
	}
	
  return(retVal);
}

/*****************************************************************************
** Function name:		I2C Stop
**
** Descriptions:		Set the I2C stop condition, if the routine
**									never exit, it's a fatal bus error.
**
** parameters:			None
** Returned value:		true or never return
** 
*****************************************************************************/

unsigned int I2C_Stop(char portNum) {
	LPC_I2C[portNum]->I2CONSET = I2CONSET_STO;      /* Set Stop flag */ 
	LPC_I2C[portNum]->I2CONCLR = I2CONCLR_SIC;  /* Clear SI flag */ 
						
	/*--- Wait for STOP detected ---*/
	while(LPC_I2C[portNum]->I2CONSET & I2CONSET_STO);

  return TRUE;
}

/*****************************************************************************
** Function name:		I2C Engine
**
** Descriptions:		The routine to complete a I2C transaction
**									from start to stop. All the intermitten
**									steps are handled in the interrupt handler.
**									Before this routine is called, the read
**									length, write length, I2C master buffer,
**									and I2C command fields need to be filled.
**									see i2cmst.c for more details. 
**
** parameters:			I2C port number
** Returned value:	master state of current I2C port.
** 
*****************************************************************************/

unsigned int I2C_Engine(char portNum) {
	if(portNum == 0) {
		RdIndex0 = 0;
		WrIndex0 = 0;
	} else if(portNum == 1) {
		RdIndex1 = 0;
		WrIndex1 = 0;
	} else {
		RdIndex2 = 0;
		WrIndex2 = 0;
	}

	/*--- Issue a start condition ---*/
  LPC_I2C[portNum]->I2CONSET = I2CONSET_STA;	/* Set Start flag */

  I2C_MasterState[portNum] = I2C_BUSY;	

  while(I2C_MasterState[portNum] == I2C_BUSY)
  {
		if(I2C_Timeout[portNum] >= I2C_MAX_TIMEOUT)
		{
			I2C_MasterState[portNum] = I2C_TIME_OUT;
			break;
		}
		I2C_Timeout[portNum]++;
  }
  LPC_I2C[portNum]->I2CONCLR = I2CONCLR_STAC;

  return (I2C_MasterState[portNum]);
}

/*****************************************************************************
** Function name:		I2C IRQHandler
**
** Descriptions:		I2C interrupt handler, deal with master mode only.
**
** parameters:			None
** Returned value:	None
** 
*****************************************************************************/

extern void I2C0_IRQHandler(void) {
	unsigned char StatValue;

  I2C_Timeout[0] = 0;
	
  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C0->I2STAT;
	
  switch(StatValue)
  {
		case 0x08:			/* A Start condition is issued. */
			WrIndex0 = 0;
			LPC_I2C0->I2DAT = I2C_MasterBuffer[0][WrIndex0++];
			LPC_I2C0->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;
		
		case 0x10:			/* A repeated started is issued */
			RdIndex0 = 0;
			/* Send SLA with R bit set, */
			LPC_I2C0->I2DAT = I2C_MasterBuffer[0][WrIndex0++];
			LPC_I2C0->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;
		
		case 0x18:			/* Regardless, it's a ACK */
			if(I2C_WriteLength[0] == 1)
			{
				LPC_I2C0->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
				I2C_MasterState[0] = I2C_NO_DATA;
			}
			else
			{
				LPC_I2C0->I2DAT = I2C_MasterBuffer[0][WrIndex0++];
			}
			LPC_I2C0->I2CONCLR = I2CONCLR_SIC;
		break;

		case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
			if(WrIndex0 < I2C_WriteLength[0])
			{   
				LPC_I2C0->I2DAT = I2C_MasterBuffer[0][WrIndex0++]; /* this should be the last one */
			} else {
				if(I2C_ReadLength[0] != 0)
				{
					LPC_I2C0->I2CONSET = I2CONSET_STA;	/* Set Repeated-start flag */
				} else {
					LPC_I2C0->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
					I2C_MasterState[0] = I2C_OK;
				}
			}
			LPC_I2C0->I2CONCLR = I2CONCLR_SIC;
		break;

		case 0x30:
			LPC_I2C0->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
			I2C_MasterState[0] = I2C_NACK_ON_DATA;
			LPC_I2C0->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x40:	/* Master Receive, SLA_R has been sent */
			if((RdIndex0 + 1) < I2C_ReadLength[0])
			{
				/* Will go to State 0x50 */
				LPC_I2C0->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
			}
			else
			{
				/* Will go to State 0x58 */
				LPC_I2C0->I2CONCLR = I2CONCLR_AAC;	/* assert NACK after data is received */
			}
			LPC_I2C0->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
			I2C_SlaveBuffer[0][RdIndex0++] = LPC_I2C0->I2DAT;
			if((RdIndex0 + 1) < I2C_ReadLength[0])
			{   
				LPC_I2C0->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
			}
			else
			{
				LPC_I2C0->I2CONCLR = I2CONCLR_AAC;	/* assert NACK on last byte */
			}
			LPC_I2C0->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x58:
			I2C_SlaveBuffer[0][RdIndex0++] = LPC_I2C0->I2DAT;
			I2C_MasterState[0] = I2C_OK;
			LPC_I2C0->I2CONSET = I2CONSET_STO;	/* Set Stop flag */ 
			LPC_I2C0->I2CONCLR = I2CONCLR_SIC;	/* Clear SI flag */
		break;

		case 0x20:		/* regardless, it's a NACK */
		case 0x48:
			LPC_I2C0->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
			I2C_MasterState[0] = I2C_NACK_ON_ADDRESS;
			LPC_I2C0->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x38:		/* Arbitration lost, in this example, we don't
						deal with multiple master situation */
		default:
			I2C_MasterState[0] = I2C_ARBITRATION_LOST;
			LPC_I2C0->I2CONCLR = I2CONCLR_SIC;	
		break;
  }
}

extern void I2C1_IRQHandler(void) {
	unsigned char StatValue;

  I2C_Timeout[1] = 0;
	
  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C1->I2STAT;
	
  switch(StatValue)
  {
		case 0x08:			/* A Start condition is issued. */
			WrIndex1 = 0;
			LPC_I2C1->I2DAT = I2C_MasterBuffer[1][WrIndex1++];
			LPC_I2C1->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;
		
		case 0x10:			/* A repeated started is issued */
			RdIndex1 = 0;
			/* Send SLA with R bit set, */
			LPC_I2C1->I2DAT = I2C_MasterBuffer[1][WrIndex1++];
			LPC_I2C1->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;
		
		case 0x18:			/* Regardless, it's a ACK */
			if(I2C_WriteLength[1] == 1)
			{
				LPC_I2C1->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
				I2C_MasterState[1] = I2C_NO_DATA;
			}
			else
			{
				LPC_I2C1->I2DAT = I2C_MasterBuffer[1][WrIndex1++];
			}
			LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
		break;

		case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
			if(WrIndex1 < I2C_WriteLength[1])
			{   
				LPC_I2C1->I2DAT = I2C_MasterBuffer[1][WrIndex1++]; /* this should be the last one */
			} else {
				if(I2C_ReadLength[1] != 0)
				{
					LPC_I2C1->I2CONSET = I2CONSET_STA;	/* Set Repeated-start flag */
				} else {
					LPC_I2C1->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
					I2C_MasterState[1] = I2C_OK;
				}
			}
			LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
		break;

		case 0x30:
			LPC_I2C1->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
			I2C_MasterState[1] = I2C_NACK_ON_DATA;
			LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x40:	/* Master Receive, SLA_R has been sent */
			if((RdIndex1 + 1) < I2C_ReadLength[1])
			{
				/* Will go to State 0x50 */
				LPC_I2C1->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
			}
			else
			{
				/* Will go to State 0x58 */
				LPC_I2C1->I2CONCLR = I2CONCLR_AAC;	/* assert NACK after data is received */
			}
			LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
			I2C_SlaveBuffer[1][RdIndex1++] = LPC_I2C1->I2DAT;
			if((RdIndex1 + 1) < I2C_ReadLength[1])
			{   
				LPC_I2C1->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
			}
			else
			{
				LPC_I2C1->I2CONCLR = I2CONCLR_AAC;	/* assert NACK on last byte */
			}
			LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x58:
			I2C_SlaveBuffer[1][RdIndex1++] = LPC_I2C1->I2DAT;
			I2C_MasterState[1] = I2C_OK;
			LPC_I2C1->I2CONSET = I2CONSET_STO;	/* Set Stop flag */ 
			LPC_I2C1->I2CONCLR = I2CONCLR_SIC;	/* Clear SI flag */
		break;

		case 0x20:		/* regardless, it's a NACK */
		case 0x48:
			LPC_I2C1->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
			I2C_MasterState[1] = I2C_NACK_ON_ADDRESS;
			LPC_I2C1->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x38:		/* Arbitration lost, in this example, we don't
						deal with multiple master situation */
		default:
			I2C_MasterState[1] = I2C_ARBITRATION_LOST;
			LPC_I2C1->I2CONCLR = I2CONCLR_SIC;	
		break;
  }
}

extern void I2C2_IRQHandler(void) {
	unsigned char StatValue;

  I2C_Timeout[2] = 0;
	
  /* this handler deals with master read and master write only */
  StatValue = LPC_I2C2->I2STAT;
	
  switch(StatValue)
  {
		case 0x08:			/* A Start condition is issued. */
			WrIndex2 = 0;
			LPC_I2C2->I2DAT = I2C_MasterBuffer[2][WrIndex2++];
			LPC_I2C2->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;
		
		case 0x10:			/* A repeated started is issued */
			RdIndex2 = 0;
			/* Send SLA with R bit set, */
			LPC_I2C2->I2DAT = I2C_MasterBuffer[2][WrIndex2++];
			LPC_I2C2->I2CONCLR = (I2CONCLR_SIC | I2CONCLR_STAC);
		break;
		
		case 0x18:			/* Regardless, it's a ACK */
			if(I2C_WriteLength[2] == 1)
			{
				LPC_I2C2->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
				I2C_MasterState[2] = I2C_NO_DATA;
			}
			else
			{
				LPC_I2C2->I2DAT = I2C_MasterBuffer[2][WrIndex2++];
			}
			LPC_I2C2->I2CONCLR = I2CONCLR_SIC;
		break;

		case 0x28:	/* Data byte has been transmitted, regardless ACK or NACK */
			if(WrIndex2 < I2C_WriteLength[2])
			{   
				LPC_I2C2->I2DAT = I2C_MasterBuffer[2][WrIndex2++]; /* this should be the last one */
			} else {
				if(I2C_ReadLength[2] != 0)
				{
					LPC_I2C2->I2CONSET = I2CONSET_STA;	/* Set Repeated-start flag */
				} else {
					LPC_I2C2->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
					I2C_MasterState[2] = I2C_OK;
				}
			}
			LPC_I2C2->I2CONCLR = I2CONCLR_SIC;
		break;

		case 0x30:
			LPC_I2C2->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
			I2C_MasterState[2] = I2C_NACK_ON_DATA;
			LPC_I2C2->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x40:	/* Master Receive, SLA_R has been sent */
			if((RdIndex2 + 1) < I2C_ReadLength[2])
			{
				/* Will go to State 0x50 */
				LPC_I2C2->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
			}
			else
			{
				/* Will go to State 0x58 */
				LPC_I2C2->I2CONCLR = I2CONCLR_AAC;	/* assert NACK after data is received */
			}
			LPC_I2C2->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x50:	/* Data byte has been received, regardless following ACK or NACK */
			I2C_SlaveBuffer[2][RdIndex2++] = LPC_I2C2->I2DAT;
			if((RdIndex2 + 1) < I2C_ReadLength[2])
			{   
				LPC_I2C2->I2CONSET = I2CONSET_AA;	/* assert ACK after data is received */
			}
			else
			{
				LPC_I2C2->I2CONCLR = I2CONCLR_AAC;	/* assert NACK on last byte */
			}
			LPC_I2C2->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x58:
			I2C_SlaveBuffer[2][RdIndex2++] = LPC_I2C2->I2DAT;
			I2C_MasterState[2] = I2C_OK;
			LPC_I2C2->I2CONSET = I2CONSET_STO;	/* Set Stop flag */ 
			LPC_I2C2->I2CONCLR = I2CONCLR_SIC;	/* Clear SI flag */
		break;

		case 0x20:		/* regardless, it's a NACK */
		case 0x48:
			LPC_I2C2->I2CONSET = I2CONSET_STO;      /* Set Stop flag */
			I2C_MasterState[2] = I2C_NACK_ON_ADDRESS;
			LPC_I2C2->I2CONCLR = I2CONCLR_SIC;
		break;
		
		case 0x38:		/* Arbitration lost, in this example, we don't
						deal with multiple master situation */
		default:
			I2C_MasterState[2] = I2C_ARBITRATION_LOST;
			LPC_I2C2->I2CONCLR = I2CONCLR_SIC;	
		break;
  }
}

/****************************************************************************
                            End Of File
****************************************************************************/
