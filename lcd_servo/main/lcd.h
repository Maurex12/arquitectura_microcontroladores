#ifndef LCD_H
#define LCD_H

#include "driver/i2c.h"
#include "esp_err.h"

/*
*****************************
* Definiciones para el I2C  *
*****************************
*/
#define I2C_MASTER_SCL_IO               22
#define I2C_MASTER_SDA_IO               21
#define I2C_MASTER_NUM                  I2C_NUM_1
#define I2C_MASTER_FREQ_HZ              100000
#define LCD_ADDR                        0x27

/**********************************
* Comandos para manejar LCD 16x02 *
***********************************
*/
#define LCD_CMD_CLEAR_DISPLAY           0x01
#define LCD_CMD_ENTRY_MODE_SET          0x04
#define LCD_CMD_DISPLAY_CONTROL         0x08
#define LCD_CMD_FUNCTION_SET            0x20
#define LCD_CMD_SET_DDRAM_ADDR          0x80


#define LCD_ENTRY_LEFT                  0x02
#define LCD_DISPLAY_ON                  0x04
#define LCD_BACKLIGHT                   0x08
#define ENABLE_BIT                      0x04

esp_err_t init_lcd(void);
esp_err_t lcd_command(uint8_t cmd);
esp_err_t lcd_data(uint8_t data);
void write_string_lcd(const char* str);

#endif 