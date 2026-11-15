#include "lcd.h"
#include "i2c.h"
#include "utick.h"
#include <stdint.h>

static uint8_t lcd_bl = LCD_PIN_BL;
static uint8_t lcd_display_ctrl = LCD_DISP_ON;

void lcd_init(void){
    lcd_port_delay_ms(50u);
    lcd_nibble(LCD_INIT_NIBBLE_8BIT,LCD_MODE_CMD);
    lcd_port_delay_ms(5u);
    lcd_nibble(LCD_INIT_NIBBLE_8BIT,LCD_MODE_CMD);
    lcd_port_delay_us(150u);
    lcd_nibble(LCD_INIT_NIBBLE_8BIT,LCD_MODE_CMD);
    lcd_port_delay_us(150u);
    lcd_nibble(LCD_INIT_NIBBLE_4BIT,LCD_MODE_CMD);
    lcd_port_delay_us(150u);
    lcd_cmd(LCD_FUNCSET_4BIT_2LINE);
    lcd_cmd(LCD_DISPLAY_OFF);
    lcd_cmd(LCD_CMD_CLEAR);
    lcd_cmd(LCD_ENTRY_DEFAULT);

    lcd_display_ctrl = LCD_DISP_ON;
    lcd_cmd(LCD_CMD_DISPLAY | lcd_display_ctrl);
}

void lcd_cmd(uint8_t cmd){
    lcd_send(cmd, LCD_MODE_CMD);
    if (cmd == LCD_CMD_CLEAR || cmd == LCD_CMD_HOME)
        lcd_port_delay_ms(LCD_DELAY_CLEAR_MS);
}

void lcd_data(uint8_t ch){
    lcd_send(ch, LCD_MODE_DATA);
}

void lcd_clear(void){
    lcd_cmd(LCD_CMD_CLEAR);
}

void lcd_home(void){
    lcd_cmd(LCD_CMD_HOME);
}

void lcd_set_cursor(uint8_t row, uint8_t col){
    lcd_cmd(LCD_CMD_SET_DDRAM | ((row ? LCD_ROW1_ADDR : LCD_ROW0_ADDR) | col));
}

void lcd_print(const char *s){
    while(*s){
        lcd_data(*s);
        ++s;
    }
}

void lcd_print_better(const char *s){
    lcd_clear();
    lcd_set_cursor(0u, 0u);
    uint8_t i = 0;
    while(*s){
        if(i == 16u){
            lcd_set_cursor(1u, 0u);
        }
        else if(i == 32u){
            lcd_set_cursor(0u, 0u);
            i = 0u;
        }
        lcd_data((uint8_t)*s);
        ++s;
        ++i;
    }
}

void lcd_backlight(uint8_t on){
    lcd_bl = (on) ? LCD_PIN_BL : 0u;
    lcd_port_write(lcd_bl);
}

void lcd_display(uint8_t on){
    if (on) lcd_display_ctrl |= LCD_DISP_ON;
    else    lcd_display_ctrl &= (uint8_t)~LCD_DISP_ON;
    lcd_cmd(LCD_CMD_DISPLAY | lcd_display_ctrl);
}

void lcd_cursor(uint8_t on, uint8_t blink){
    lcd_display_ctrl &= (uint8_t)~(LCD_DISP_CURSOR | LCD_DISP_BLINK);
    if (on)    lcd_display_ctrl |= LCD_DISP_CURSOR;
    if (blink) lcd_display_ctrl |= LCD_DISP_BLINK;
    lcd_cmd(LCD_CMD_DISPLAY | lcd_display_ctrl);
}

void lcd_nibble(uint8_t nib, uint8_t rs){
    uint8_t d = (uint8_t)(((nib & 0xF) << LCD_DATA_SHIFT) | lcd_bl | rs);
    lcd_port_write(d | LCD_PIN_E);
    lcd_port_write(d);
}

void lcd_send(uint8_t byte, uint8_t rs){
    lcd_nibble(byte>>4 ,rs);
    lcd_nibble((byte & 0xF), rs);
}

int lcd_port_write(uint8_t byte){
    if (I2C_Start(LPI2C0, LCD_I2C_ADDR_7BIT, false) != I2C_OK) {
        I2C_Stop(LPI2C0);
        return 0;
    }
    if (I2C_WriteByte(LPI2C0, byte) != I2C_OK) {
        I2C_Stop(LPI2C0);
        return 0;
    }
    I2C_Stop(LPI2C0);
    return 1;
}

inline void lcd_port_delay_us(uint32_t us){
    delay_us(us);
}

inline void lcd_port_delay_ms(uint32_t ms){
    delay_ms(ms);
}
