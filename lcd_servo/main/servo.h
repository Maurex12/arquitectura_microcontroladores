#include "driver/mcpwm.h"


#define SERVO_PIN 18                                        // Salida señal PWM para el servo
#define FREQUENCY 50                                        // Frecuencia en Hz del PWM
#define MIN_DUTY_US 500                                     // Ancho de pulso mínimo en microsegundos (servo SG90)
#define MAX_DUTY_US 2400                                    // Ancho de pulso máximo en microsegundos (servo SG90)


void init_servo();
void setPosition_servo(int angle);