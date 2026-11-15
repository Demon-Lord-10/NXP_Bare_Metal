#ifndef LCD_I2C_H
#define LCD_I2C_H

#include <stdint.h>
#include "i2c.h"

/* ---------- I2C ---------- */
#define LCD_I2C_ADDR_7BIT       0x27u   /* 0x3F if PCF8574A */
#define LCD_I2C_ADDR_SHIFTED    (LCD_I2C_ADDR_7BIT << 1)
#define LCD_I2C_TIMEOUT_MS      100u

/* ---------- PCF8574 pin -> LCD pin mapping ----------
 * bit: 7   6   5   4   3   2  1   0
 *      D7  D6  D5  D4  BL  E  RW  RS
 * Change these if your backpack is wired differently. */
#define LCD_PIN_RS              (1u << 0)
#define LCD_PIN_RW              (1u << 1)
#define LCD_PIN_E               (1u << 2)
#define LCD_PIN_BL              (1u << 3)
#define LCD_DATA_SHIFT          4u      /* DB4..DB7 on P4..P7 */

/* RS selection for lcd_send() */
#define LCD_MODE_CMD            0u
#define LCD_MODE_DATA           LCD_PIN_RS

/* ---------- Geometry ---------- */
#define LCD_COLS                16u
#define LCD_ROWS                2u
#define LCD_ROW0_ADDR           0x00u
#define LCD_ROW1_ADDR           0x40u   /* DDRAM line 2 start */

/* ---------- Commands (datasheet p.11) ---------- */
#define LCD_CMD_CLEAR           0x01u
#define LCD_CMD_HOME            0x02u

/* Entry mode set: 0000 01 I/D S */
#define LCD_CMD_ENTRY           0x04u
#define LCD_ENTRY_INC           0x02u   /* I/D=1 increment */
#define LCD_ENTRY_SHIFT         0x01u   /* S=1 display shift */

/* Display on/off: 0000 1 D C B */
#define LCD_CMD_DISPLAY         0x08u
#define LCD_DISP_ON             0x04u   /* D */
#define LCD_DISP_CURSOR         0x02u   /* C */
#define LCD_DISP_BLINK          0x01u   /* B */

/* Cursor/display shift: 0001 S/C R/L * * */
#define LCD_CMD_SHIFT           0x10u
#define LCD_SHIFT_DISPLAY       0x08u   /* S/C=1 display, 0 cursor */
#define LCD_SHIFT_RIGHT         0x04u   /* R/L=1 right, 0 left */

/* Function set: 001 DL N F * * */
#define LCD_CMD_FUNCSET         0x20u
#define LCD_FS_8BIT             0x10u   /* DL=1 (0 = 4-bit) */
#define LCD_FS_2LINE            0x08u   /* N=1 */
#define LCD_FS_5X10             0x04u   /* F=1 (0 = 5x7) */

#define LCD_CMD_SET_CGRAM       0x40u   /* | 6-bit CGRAM addr */
#define LCD_CMD_SET_DDRAM       0x80u   /* | 7-bit DDRAM addr */

/* Handy presets */
#define LCD_FUNCSET_4BIT_2LINE  (LCD_CMD_FUNCSET | LCD_FS_2LINE)           /* 0x28 */
#define LCD_ENTRY_DEFAULT       (LCD_CMD_ENTRY | LCD_ENTRY_INC)            /* 0x06 */
#define LCD_DISPLAY_OFF         (LCD_CMD_DISPLAY)                          /* 0x08 */
#define LCD_DISPLAY_ON_NOCUR    (LCD_CMD_DISPLAY | LCD_DISP_ON)            /* 0x0C */
#define LCD_DISPLAY_ON_CUR_BLK  (LCD_CMD_DISPLAY | LCD_DISP_ON | \
                                 LCD_DISP_CURSOR | LCD_DISP_BLINK)         /* 0x0F */

/* ---------- Init sequence nibbles (datasheet p.10) ---------- */
#define LCD_INIT_NIBBLE_8BIT    0x3u
#define LCD_INIT_NIBBLE_4BIT    0x2u

/* ---------- Timing (datasheet p.9, p.10, p.11) ---------- */
#define LCD_DELAY_POWERUP_MS    50u     /* spec: >15 ms after VDD > 4.5V */
#define LCD_DELAY_INIT1_MS      5u      /* spec: >4.1 ms */
#define LCD_DELAY_INIT2_US      150u    /* spec: >100 us */
#define LCD_DELAY_CMD_US        50u     /* spec: 40 us */
#define LCD_DELAY_CLEAR_MS      2u      /* spec: 1.64 ms (clear/home) */
#define LCD_E_PULSE_MIN_NS      450u    /* E pulse width min */
#define LCD_E_CYCLE_MIN_NS      1000u   /* E cycle time min */

/* ---------- Low-level hooks: implement per platform ---------- */
int  lcd_port_write(uint8_t byte);      /* one I2C byte to PCF8574, 0 = ok */
void lcd_port_delay_us(uint32_t us);
void lcd_port_delay_ms(uint32_t ms);

/* ---------- Public API ---------- */
void lcd_init(void);
void lcd_cmd(uint8_t cmd);
void lcd_data(uint8_t ch);
void lcd_clear(void);
void lcd_home(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *s);
void lcd_backlight(uint8_t on);
void lcd_display(uint8_t on);
void lcd_cursor(uint8_t on, uint8_t blink);
void lcd_nibble(uint8_t nib, uint8_t rs);
void lcd_send(uint8_t byte, uint8_t rs);

#endif /* LCD_I2C_H */
