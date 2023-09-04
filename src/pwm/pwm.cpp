#include "pwm/pwm.h"

void configPWM(){

    mcpwm_config_t pwm_config;

    pwm_config.frequency = 5000;   
    pwm_config.cmpr_a = 0;
    pwm_config.cmpr_b = 0; 
    pwm_config.counter_mode = MCPWM_UP_COUNTER;   // para MCPWM assimetrico
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;     // define o duty cicle em nivel alto

    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, PWMA);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0B, PWMB);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, PWMC);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1B, PWMD);
} 

void pwmASetDuty(float duty){
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty);
}

void pwmBSetDuty(float duty){
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_B, duty);
}

void pwmCSetDuty(float duty){
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, duty);
}

void pwmDSetDuty(float duty){
    mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_B, duty);
}