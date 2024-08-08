#include <stdio.h>
#include "servo.h"
#include "lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

char angulo_str[20];

void app_main(void) 
{
    ESP_ERROR_CHECK(init_lcd());
    init_servo();

    lcd_command(LCD_CMD_SET_DDRAM_ADDR | 0x00);                             // Set cursor en primera línea
    write_string_lcd("Posicion servo:");                                    // Envío mensaje en primera línea
    

     while (1) 
    {
        for (int angle = 0; angle <= 180; angle += 10) 
        {
            setPosition_servo(angle);                                       // Obtengo posición del servo
            snprintf(angulo_str, sizeof(angulo_str), "Angulo %d", angle);

            lcd_command(LCD_CMD_SET_DDRAM_ADDR | 0x40);                     // Set cursor en segunda línea
            write_string_lcd("            ");                               // Limpio segunda línea del LCD

            lcd_command(LCD_CMD_SET_DDRAM_ADDR | 0x40);
            write_string_lcd(angulo_str);
            vTaskDelay(pdMS_TO_TICKS(1000));                                // Espera 1 segundo
        }

        for (int angle = 180; angle >= 0; angle -= 10) 
        {
            setPosition_servo(angle);
            snprintf(angulo_str, sizeof(angulo_str), "Angulo %d", angle);

            lcd_command(LCD_CMD_SET_DDRAM_ADDR | 0x40);                     // Set cursor en segunda línea
            write_string_lcd("            ");                               // Limpio segunda línea del LCD

            lcd_command(LCD_CMD_SET_DDRAM_ADDR | 0x40);
            write_string_lcd(angulo_str);
            vTaskDelay(pdMS_TO_TICKS(1000));                                // Espera 1 segundo
        }
    }
}
