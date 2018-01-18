#include "main.h"

void system_clock_init(void)
{
	FLASH->ACR |= FLASH_ACR_LATENCY_1WS;	/* enable 1 wait stait (2 CPU cycles) lattency  for flash memory */
	FLASH->ACR |= FLASH_ACR_PRFTEN;			/* enable prefetch */
	
	RCC->CR |= RCC_CR_HSEON;				/* enable HSE oscillator */
	while ((RCC->CR & RCC_CR_HSERDY) == 0);	/* wait till HSE oscillator is ready */

	// RCC->CR |= RCC_CR_CSSON; 			/* enable clock security system */ 	

	RCC->CFGR |= RCC_CFGR_HPRE_DIV2 | 		/* AHB prescaler set to 2 */
				 RCC_CFGR_PPRE1_DIV2 |  	/* APB1 prescaler set to 2 */
				 RCC_CFGR_PPRE2_DIV1;		/* APB2 prescaler set to 1 */
	RCC->CFGR &= ~RCC_CFGR_I2SSRC;			/* PLLI2S used as I2S clock source */
	
	
	/* Configure main PLL */
	RCC->PLLCFGR = 0;								/* clear PLLCFGR register */
	RCC->PLLCFGR |= (8 << RCC_PLLCFGR_PLLM_Pos) |	/* PLLM prescaler set to 8 */
					(192 << RCC_PLLCFGR_PLLN_Pos) |	/* PLLN multiplier set to 192 */
					(0 << RCC_PLLCFGR_PLLP_Pos) |	/* PLLP divisor set to 2 (00: 2, 01: 4, 10: 6, 11: 8)*/
					(4 << RCC_PLLCFGR_PLLQ_Pos) |	/* PLLQ divisor set to 4 */
					(RCC_PLLCFGR_PLLSRC_HSE);		/* set HSE as source for PLL */

	
	RCC->CR |= RCC_CR_PLLON;						/* enable PLL */
	while ((RCC->CR & RCC_CR_PLLRDY) == 0)			/* wait till PLL is ready */
	
	RCC->CFGR &= ~RCC_CFGR_SW;						/* select PLL as system clock */
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);	/* wait till PLL is used*/
	
	SystemCoreClockUpdate();						/* update SystemCoreClock variable */
}
