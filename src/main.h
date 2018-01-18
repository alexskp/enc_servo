#ifndef MAIN_H_
#define MAIN_H_

#include <stm32f4xx.h>

/* define external crystal frequency */
//#define HSE_VALUE ((uint32_t)8000000)

/* servo angle constants */
#define SERVO_TURN	100
#define SERVO_0 	500
#define SERVO_90	1400
#define SERVO_180	2300

void system_clock_init(void);
void servo_init(void);
void encoder_init(void);
void encoder_btn_init(void);
void leds_init(void);

#endif
