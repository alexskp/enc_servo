
#include <stdint.h>
#include "main.h"

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF;				/* clear update interrupt flag */
	if (TIM3->CR1 & TIM_CR1_DIR)			/* if count direction bit is 1 */
	{
		if (TIM4->CCR4 < SERVO_180)			/* if servo < 180 degree */
		{
			GPIOD->ODR |= GPIO_ODR_OD12;	/* turn on direction LED */
			TIM4->CCR4 += SERVO_TURN;		/* turn servo to 15 degree */
		}
	}
	else	 								/* if count direction bit is 0 */
	{
		if (TIM4->CCR4 > SERVO_0)			/* if servo > 0 degree */
		{
			GPIOD->ODR |= GPIO_ODR_OD14;	/* turn on direction LED */
			TIM4->CCR4 -= SERVO_TURN;		/* turn servo to 15 degree */
		}
	}	
	for (volatile uint32_t i = 10000; i > 0; i--);		/* program debounce delay */
	GPIOD->ODR &= ~(GPIO_ODR_OD12 | GPIO_ODR_OD14);		/* turn off direction leds */
}

void EXTI3_IRQHandler(void)
{
	TIM4->CCR4 = SERVO_90;					/* set servo to stock position 90 degree */
	EXTI->PR |= EXTI_PR_PR3;				/* clear pending bit */
}

int main(void)
{
	system_clock_init();		/* system clock initialization */
	servo_init();				/* servo initialization */
	encoder_init();				/* encoder initialization */
	encoder_btn_init();			/* encoder button initialization */
	leds_init();				/* LEDs initialization */
	
	while (1)
	{

	}
}
