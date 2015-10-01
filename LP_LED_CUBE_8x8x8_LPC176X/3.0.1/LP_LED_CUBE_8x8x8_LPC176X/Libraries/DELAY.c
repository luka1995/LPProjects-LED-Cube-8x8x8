/****************************************************************************
	Luka Penger 2013
	DELAY
	LPC17xx
****************************************************************************/

#include "DELAY.h"

void delayMs(uint8_t timer_num, uint32_t delayInMs)
{
  if(timer_num == 0)
  {
		LPC_TIM0->TCR = 0x02;                /* reset timer */
		LPC_TIM0->PR  = 0x00;                /* set prescaler to zero */
		LPC_TIM0->MR0 = delayInMs * (SystemCoreClock / 1000); // 23980 = 1ms
		LPC_TIM0->IR  = 0xff;                /* reset all interrrupts */
		LPC_TIM0->MCR = 0x04;                /* stop timer on match */
		LPC_TIM0->TCR = 0x01;                /* start timer */

		/* wait until delay time has elapsed */
		while (LPC_TIM0->TCR & 0x01);
  }
  else if(timer_num == 1)
  {
		LPC_TIM1->TCR = 0x02;                /* reset timer */
		LPC_TIM1->PR  = 0x00;                /* set prescaler to zero */
		LPC_TIM1->MR0 = delayInMs * (SystemCoreClock / 1000); // 23980 = 1ms
		LPC_TIM1->IR  = 0xff;                /* reset all interrrupts */
		LPC_TIM1->MCR = 0x04;                /* stop timer on match */
		LPC_TIM1->TCR = 0x01;                /* start timer */

		/* wait until delay time has elapsed */
		while (LPC_TIM1->TCR & 0x01);
  }
	else if(timer_num == 2)
  {
		LPC_TIM2->TCR = 0x02;                /* reset timer */
		LPC_TIM2->PR  = 0x00;                /* set prescaler to zero */
		LPC_TIM2->MR0 = delayInMs * (SystemCoreClock / 1000); // 23980 = 1ms
		LPC_TIM2->IR  = 0xff;                /* reset all interrrupts */
		LPC_TIM2->MCR = 0x04;                /* stop timer on match */
		LPC_TIM2->TCR = 0x01;                /* start timer */

		/* wait until delay time has elapsed */
		while (LPC_TIM2->TCR & 0x01);
  }
	else if(timer_num == 3)
  {
		LPC_TIM3->TCR = 0x02;                /* reset timer */
		LPC_TIM3->PR  = 0x00;                /* set prescaler to zero */
		LPC_TIM3->MR0 = delayInMs * (SystemCoreClock / 1000); // 23980 = 1ms
		LPC_TIM3->IR  = 0xff;                /* reset all interrrupts */
		LPC_TIM3->MCR = 0x04;                /* stop timer on match */
		LPC_TIM3->TCR = 0x01;                /* start timer */

		/* wait until delay time has elapsed */
		while (LPC_TIM3->TCR & 0x01);
  }
}

/****************************************************************************
                            End Of File
****************************************************************************/
