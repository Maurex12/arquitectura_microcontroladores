#include "servo.h"
#include "driver/mcpwm.h"


/*
*****************************
* Inicialización del servo  *
*****************************
*/

void init_servo() 
{
    mcpwm_config_t pwm_config;
    pwm_config.frequency = FREQUENCY;                       
    pwm_config.cmpr_a = 0;                                  // Inicialmente el duty cycle es 0%
    pwm_config.cmpr_b = 0;                                  // Inicialmente el duty cycle es 0%
    pwm_config.counter_mode = MCPWM_UP_COUNTER;             // Contador hacia arriba
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;               
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);
    
    
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, SERVO_PIN);
}

/*
******************************
* Obtengo posición del servo *
******************************
*/

void setPosition_servo(int angle) 
{
    
    int pulse_width_us = MIN_DUTY_US + (angle / 180.0) * (MAX_DUTY_US - MIN_DUTY_US);       // Ancho del pulso del servo
    float duty_cycle = (pulse_width_us * 100.0) / (1000000 / FREQUENCY);                    // Calcula el duty cycle
    
   mcpwm_set_duty(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, duty_cycle);
}