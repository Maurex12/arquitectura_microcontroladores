#include "lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "esp_log.h"

/*
*************************************
* Configuración del I2C como master *
*************************************
*/

static esp_err_t i2c_master_init(void) 
{
    i2c_config_t config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    esp_err_t ret = i2c_param_config(I2C_MASTER_NUM, &config);

    if (ret != ESP_OK) 
    {
        return ret;
    }

    return i2c_driver_install(I2C_MASTER_NUM, config.mode, 0, 0, 0);
}

static esp_err_t lcd_write_nibble(uint8_t data) 
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (LCD_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, data | LCD_BACKLIGHT, true);
    i2c_master_write_byte(cmd, data | ENABLE_BIT | LCD_BACKLIGHT, true);
    i2c_master_write_byte(cmd, (data & ~ENABLE_BIT) | LCD_BACKLIGHT, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);
    vTaskDelay(pdMS_TO_TICKS(2));  

    return ret;
}

static esp_err_t lcd_write_byte(uint8_t data, uint8_t mode) 
{
    esp_err_t ret = lcd_write_nibble(mode | (data & 0xF0));

    if (ret != ESP_OK) 
    {
        return ret;
    }

    return lcd_write_nibble(mode | ((data << 4) & 0xF0));
}


/*
***************************************
* Función para enviar comandos al LCD *
***************************************
*/

esp_err_t lcd_command(uint8_t cmd) 
{
    return lcd_write_byte(cmd, 0);
}


/*
************************************
* Función para enviar datos al LCD *
************************************
*/

esp_err_t lcd_data(uint8_t data) 
{
    return lcd_write_byte(data, 1);
}


/*
**************************
* Inicialización del LCD *
**************************
*/

esp_err_t init_lcd(void) {
    ESP_ERROR_CHECK(i2c_master_init());

    // Inicialización LCD en modo 8 bits
    vTaskDelay(pdMS_TO_TICKS(50)); 
    lcd_write_nibble(0x30);                                 
    vTaskDelay(pdMS_TO_TICKS(5)); 
    lcd_write_nibble(0x30);  
    vTaskDelay(pdMS_TO_TICKS(1)); 
    lcd_write_nibble(0x30);  

    // Inicialización LCD en modo 4 bits
    lcd_write_nibble(0x20);  

    lcd_command(LCD_CMD_FUNCTION_SET | 0x08);                       // 2 lines, 5x8 font
    lcd_command(LCD_CMD_DISPLAY_CONTROL | LCD_DISPLAY_ON);          // Display ON
    lcd_command(LCD_CMD_CLEAR_DISPLAY);                             // Limpio todo el Display
    lcd_command(LCD_CMD_ENTRY_MODE_SET | LCD_ENTRY_LEFT);           

    return ESP_OK;
}

/*
***************************
* Escribo mensajes en LCD *
***************************
*/

void write_string_lcd(const char* str) 
{
    while (*str) 
    {
        lcd_data((uint8_t)(*str));
        str++;
    }
}