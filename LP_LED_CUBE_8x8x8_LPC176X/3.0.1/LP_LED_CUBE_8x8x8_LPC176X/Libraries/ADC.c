/****************************************************************************
	Luka Penger 2013
	ADC
	LPC17xx
****************************************************************************/

#include "ADC.h"


#ifndef _BV
#define _BV(_x_) (1UL << (_x_))
#endif

volatile uint32_t ADCValue[ADC_NUM];
volatile uint32_t ADCIntDone = 0;
volatile uint32_t BurstCounter = 0;
volatile uint32_t OverRunCounter = 0;

#if BURST_MODE
volatile uint32_t channel_flag = 0; 
#endif

#if ADC_INTERRUPT_FLAG
/******************************************************************************
** Function name:		ADC_IRQHandler
**
** Descriptions:		ADC interrupt handler
**
** parameters:			None
** Returned value:	None
** 
******************************************************************************/
void ADC_IRQHandler(void) {
  uint32_t regVal;
  volatile uint32_t dummy;
  int i;
  
  regVal = LPC_ADC->ADSTAT;		/* Read ADC will clear the interrupt */
  if(regVal & 0x0000FF00)	{		/* check OVERRUN error first */
		OverRunCounter++;
		
  	for (i = 0; i < ADC_NUM; i++ ) {
  	  regVal = (regVal & 0x0000FF00) >> 0x08;
  	  /* if overrun, just read ADDR to clear */
  	  /* regVal variable has been reused. */
      if (regVal & _BV(i)) {
				switch (i) {
					case 0: dummy = LPC_ADC->ADDR0; break;
					case 1: dummy = LPC_ADC->ADDR1; break;
					case 2: dummy = LPC_ADC->ADDR2; break;
					case 3: dummy = LPC_ADC->ADDR3; break;
					case 4: dummy = LPC_ADC->ADDR4; break;
					case 5: dummy = LPC_ADC->ADDR5; break;
					case 6: dummy = LPC_ADC->ADDR6; break;
					case 7: dummy = LPC_ADC->ADDR7; break;
				}
  	  }
  	}
		
		LPC_ADC->ADCR &= ~((0x7<<24)|(0x1<<16));	/* stop ADC now, turn off BURST bit. */ 
  	ADCIntDone = 1;
  	return;	
  }

  for ( i = 0; i < ADC_NUM; i++ ) {
    if (regVal & _BV(i)) {
			switch (i) {
				case 0: ADCValue[i] = ( LPC_ADC->ADDR0 >> 4 ) & 0xFFF; break;
				case 1: ADCValue[i] = ( LPC_ADC->ADDR1 >> 4 ) & 0xFFF; break;
				case 2: ADCValue[i] = ( LPC_ADC->ADDR2 >> 4 ) & 0xFFF; break;
				case 3: ADCValue[i] = ( LPC_ADC->ADDR3 >> 4 ) & 0xFFF; break;
				case 4: ADCValue[i] = ( LPC_ADC->ADDR4 >> 4 ) & 0xFFF; break;
				case 5: ADCValue[i] = ( LPC_ADC->ADDR5 >> 4 ) & 0xFFF; break;
				case 6: ADCValue[i] = ( LPC_ADC->ADDR6 >> 4 ) & 0xFFF; break;
				case 7: ADCValue[i] = ( LPC_ADC->ADDR7 >> 4 ) & 0xFFF; break;
			}
		}
  }

#if BURST_MODE
  BurstCounter++;
  channel_flag |= (regVal & 0xFF);
	
  if ((channel_flag & 0xFF) == 0xFF) {
		/* All the bits in have been set, it indicates all the ADC 
		channels have been converted. */
		LPC_ADC->ADCR &= ~(0x1<<16);	/* Clear BURST mode, stop ADC now */ 
  	channel_flag = 0; 
		ADCIntDone = 1;
  }
#else
  LPC_ADC->ADCR &= ~(0x7<<24);	/* stop ADC now */ 
  ADCIntDone = 1;
#endif
  return;
}
#endif

/*****************************************************************************
** Function name:		ADCInit
**
** Descriptions:		initialize ADC channel
**
** parameters:			ADC clock rate
** Returned value:	None
** 
*****************************************************************************/

void ADC_Init(uint32_t ADC_Clk) {
  uint32_t i, pclkdiv, pclk;

  /* Enable CLOCK into ADC controller */
  LPC_SC->PCONP |= (1 << 12);

  for ( i = 0; i < ADC_NUM; i++ ) {
		ADCValue[i] = 0x0;
  }

  /* all the related pins are set to ADC inputs, AD0.0~7 */
  LPC_PINCON->PINSEL0 &= ~0x000000F0;	/* P0.2~3, A0.6~7, function 10 */
  LPC_PINCON->PINSEL0 |= 0x000000A0;	
  LPC_PINCON->PINSEL1 &= ~0x003FC000;	/* P0.23~26, A0.0~3, function 01 */
  LPC_PINCON->PINSEL1 |= 0x00154000;
  LPC_PINCON->PINSEL3 |= 0xF0000000;	/* P1.30~31, A0.4~5, function 11 */
  /* No pull-up no pull-down (function 10) on these ADC pins. */
  LPC_PINCON->PINMODE0 &= ~0x000000F0;
  LPC_PINCON->PINMODE0 |= 0x000000A0;
  LPC_PINCON->PINMODE1 &= ~0x003FC000;
  LPC_PINCON->PINMODE1 |= 0x002A8000;
  LPC_PINCON->PINMODE3 &= ~0xF0000000;
  LPC_PINCON->PINMODE3 |= 0xA0000000;

  /* By default, the PCLKSELx value is zero, thus, the PCLK for
  all the peripherals is 1/4 of the SystemFrequency. */
  /* Bit 24~25 is for ADC */
  pclkdiv = (LPC_SC->PCLKSEL0 >> 24) & 0x03;
	
  switch(pclkdiv) {
		case 0x00:
		default:
			pclk = SystemCoreClock/4;
			break;
		case 0x01:
			pclk = SystemCoreClock;
			break; 
		case 0x02:
			pclk = SystemCoreClock/2;
			break; 
		case 0x03:
			pclk = SystemCoreClock/8;
			break;
  }

  LPC_ADC->ADCR = ( 0x01 << 0 ) |  /* SEL=1,select channel 0~7 on ADC0 */
		( ( pclk  / ADC_Clk - 1 ) << 8 ) |  /* CLKDIV = Fpclk / ADC_Clk - 1 */ 
		( 0 << 16 ) | 		/* BURST = 0, no BURST, software controlled */
		( 0 << 17 ) |  		/* CLKS = 0, 11 clocks/10 bits */
		( 1 << 21 ) |  		/* PDN = 1, normal operation */
		( 0 << 24 ) |  		/* START = 0 A/D conversion stops */
		( 0 << 27 );		/* EDGE = 0 (CAP/MAT singal falling,trigger A/D conversion) */ 

  /* If POLLING, no need to do the following */
#if ADC_INTERRUPT_FLAG
  NVIC_EnableIRQ(ADC_IRQn);
#if BURST_MODE
  LPC_ADC->ADINTEN = 0xFF;		/* Enable all interrupts */
#else
  LPC_ADC->ADINTEN = 0x1FF;		/* Enable all interrupts */
#endif
#endif
  return;
}

/*****************************************************************************
** Function name:		ADC_Read
**
** Descriptions:		Read ADC channel
**
** parameters:			Channel number
** Returned value:	Value read, if interrupt driven, return channel #
** 
*****************************************************************************/

uint32_t ADC_Read(uint8_t channelNum) {
	#if !ADC_INTERRUPT_FLAG
		uint32_t regVal = 0, ADC_Data;
	#endif

  /* channel number is 0 through 7 */
  if(channelNum >= ADC_NUM) {
		channelNum = 0;		/* reset channel number to 0 */
  }

  LPC_ADC->ADCR &= 0xFFFFFF00;
  LPC_ADC->ADCR |= (1 << 24) | (1 << channelNum);	
	
	/* switch channel,start A/D convert */
	#if !ADC_INTERRUPT_FLAG
		while(1)	{		/* wait until end of A/D convert */
			switch (channelNum) {
				case 0: regVal = LPC_ADC->ADDR0; break;
				case 1: regVal = LPC_ADC->ADDR1; break;
				case 2: regVal = LPC_ADC->ADDR2; break;
				case 3: regVal = LPC_ADC->ADDR3; break;
				case 4: regVal = LPC_ADC->ADDR4; break;
				case 5: regVal = LPC_ADC->ADDR5; break;
				case 6: regVal = LPC_ADC->ADDR6; break;
				case 7: regVal = LPC_ADC->ADDR7; break;
			}

			/* read result of A/D conversion */
			if(regVal & ADC_DONE) {
				break;
			}
		}	
        
		LPC_ADC->ADCR &= 0xF8FFFFFF;	/* stop ADC now */  
  
		/* save data when it's not overrun, otherwise, return zero */
		if(regVal & ADC_OVERRUN )	{
			return ( 0 );
		}
		
		ADC_Data = ( regVal >> 4 ) & 0xFFF;
		return ( ADC_Data );	/* return A/D conversion value */
	#else
		return ( channelNum );	/* if it's interrupt driven, the ADC reading is done inside the handler. so, return channel number */
	#endif
}

/*****************************************************************************
** Function name:		ADC_BurstRead
**
** Descriptions:		Use burst mode to convert multiple channels once.
**
** parameters:			None
** Returned value:	None
** 
*****************************************************************************/

void ADC_BurstRead(void) {
  /* Start bits need to be zero before BURST mode can be set. */
  if (LPC_ADC->ADCR & (0x7<<24)) {
		LPC_ADC->ADCR &= ~(0x7<<24);
  }
	
  LPC_ADC->ADCR &= ~0xFF;
  /* Read all channels, 0 through 7. */
  LPC_ADC->ADCR |= 0xFF;
  LPC_ADC->ADCR |= (0x1<<16);		/* Set burst mode and start A/D convert */
  return;						/* the ADC reading is done inside the handler, return 0. */
}

/****************************************************************************
                            End Of File
****************************************************************************/
