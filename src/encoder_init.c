#include "main.h"

void encoder_init(void)
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	/* GPIOB clock enable */
	GPIOB->MODER |= GPIO_MODER_MODE4_1;		/* use alternative function */
	GPIOB->MODER &= ~GPIO_MODER_MODE4_0;	
	GPIOB->MODER |= GPIO_MODER_MODE5_1;		/* use alternative function */
	GPIOB->MODER &= ~GPIO_MODER_MODE5_0;	
	GPIOB->PUPDR |= (GPIO_PUPDR_PUPD4_0 |	/* use pull-up resistor */
					GPIO_PUPDR_PUPD5_0);
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED4_1;		/* fast speed */
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED4_0;
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_1;		/* fast speed */
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5_0;
	
	GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL4_1);		/* select TIM3 as alternative function for GPIOB 4 */
	GPIOB->AFR[0] |= (GPIO_AFRL_AFSEL5_1);		/* select TIM3 as alternative function for GPIOB 5 */
	
	TIM3->CCMR1 |= (TIM_CCMR1_IC1F_0 |			/* digital filter configaration */
					TIM_CCMR1_IC1F_1 |			/* sampling speed = ck_int, 8 samples */
					TIM_CCMR1_IC2F_0 |
					TIM_CCMR1_IC2F_1);

	TIM3->CCMR1 |= (TIM_CCMR1_CC1S_0 |			/* channel 1 configured as input mapped on TI1 */
					TIM_CCMR1_CC2S_0);			/* channel 2 configured as input mapped on TI2 */
					
	TIM3->CCER &= ~(TIM_CCER_CC1P |				/* rising edge */
					TIM_CCER_CC2P);
					
	TIM3->SMCR |= (TIM_SMCR_SMS_0 |				/* encoder mode 3 - counter counts up/down on both TI1FP1 */
					TIM_SMCR_SMS_1);			/* and TI2FP2 edges depending on the level of the other input */
	
	TIM3->DIER |= TIM_DIER_UIE;					/* update interrupt enable */
	
	TIM3->ARR = 3;								/* count to 3 */			
	TIM3->CR1 |= TIM_CR1_CEN;					/* enable timer */
	TIM3->CNT = 0;								/* clear CNT */
	
	NVIC_EnableIRQ(TIM3_IRQn);					/* enable interrupt request for timer 3 */
}

void encoder_btn_init(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;		/* GPIOB clock enable */
	
	GPIOB->MODER |= GPIO_MODER_MODE3_1;			/* use alternative function */
	GPIOB->MODER &= ~GPIO_MODER_MODE3_0;	
	
	GPIOB->PUPDR |= GPIO_PUPDR_PUPD3_0;			/* use pull-up resistor */
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPD3_1;
	
	GPIOB->OSPEEDR |= GPIO_OSPEEDR_OSPEED3_1;	/* fast speed */
	GPIOB->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED3_0;
	
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI3_PB;	/* use PB3 pin for external interrupt */
	
	EXTI->FTSR |= EXTI_FTSR_TR3;				/* interrupt by falling edge */
	EXTI->IMR |= EXTI_IMR_MR3;					/* interrupt request from line 3 is not masked */
	
	NVIC_EnableIRQ(EXTI3_IRQn);					/* enable interrupt request */
}
