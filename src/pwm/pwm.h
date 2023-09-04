#include <Arduino.h>
#include "driver/mcpwm.h"

#ifndef PWM_H
#define PWM_H

#define PWMA GPIO_NUM_21 // PWMA
#define PWMB GPIO_NUM_19 // PWMB
#define PWMC GPIO_NUM_18 // PWMC
#define PWMD GPIO_NUM_5  // PWMD

void configPWM();

void pwmASetDuty(float duty);
void pwmBSetDuty(float duty);
void pwmCSetDuty(float duty);
void pwmDSetDuty(float duty);

#endif