#include "main.h"

void servo_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;		/* timer 4 clock enable */
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;	/* GPIOD clock enable */
	GPIOD->MODER |= GPIO_MODER_MODE15_1;	/* use alternative function */
	GPIOD->MODER &= ~GPIO_MODER_MODE15_0;	
	GPIOD->OSPEEDR |= GPIO_OSPEEDR_OSPEED15_1;	/* fast speed */
	GPIOD->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED15_0;
	GPIOD->AFR[1] |= (GPIO_AFRH_AFSEL15_1);		/* select TIM4 as alternative function for GPIOD 15*/
	
	/* clock frequency 48MHz */
	
	TIM4->PSC = 48 - 1;					/* set prescaler to 48 to get 1MHz timer count frequency*/
	TIM4->CCMR2 |= (TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1);	 /* select PWM mode 1 OCxM = 0b110 */
	TIM4->CCER |= (TIM_CCER_CC4E);		/* select channel 4 for PWM output */
	TIM4->ARR = 20000;					/* period */
	TIM4->CCR4 = SERVO_90;				/* initial duty cycle */
	TIM4->CR1 |= TIM_CR1_CEN;			/* enable TIMER4 */
}
