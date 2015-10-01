/****************************************************************************
	Luka Penger 2013
	ADC
	LPC17xx
****************************************************************************/
#ifndef __ADC_H 
#define __ADC_H 

#include <LPC17xx.h>
#include <type.h>

/* In DMA mode, BURST mode and ADC_INTERRUPT flag need to be set. */
/* In BURST mode, ADC_INTERRUPT need to be set. */

#define ADC_INTERRUPT_FLAG	1					/* 1 is interrupt driven, 0 is polling */
#define BURST_MODE					0   			/* Burst mode works in interrupt driven mode only. */
#define ADC_DEBUG						0

#define ADC_OFFSET          0x10
#define ADC_INDEX           4

#define ADC_DONE            0x80000000
#define ADC_OVERRUN         0x40000000
#define ADC_ADINT           0x00010000

#define ADC_NUM							8					/* for LPCxxxx */
#define ADC_CLK							1000000		/* set to 1Mhz */

extern void ADC_IRQHandler(void);
void ADC_Init(uint32_t ADC_Clk);
uint32_t ADC_Read(uint8_t channelNum);
void ADC_BurstRead(void);

#endif /* end __ADC_H */
/****************************************************************************
                            End Of File
****************************************************************************/
