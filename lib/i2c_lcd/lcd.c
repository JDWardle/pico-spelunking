/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "i2c/lcd.h"

/* Quick helper function for single byte transfers */
void i2c_write_byte(uint8_t val)
{
#ifdef i2c_default
    i2c_write_blocking(i2c_default, DEFAULT_LCD_ADDR, &val, 1, false);
#endif
}

void lcd_toggle_enable(uint8_t val)
{
    // Toggle enable pin on LCD display
    // We cannot do this too quickly or things don't work
    sleep_us(DELAY_US);
    i2c_write_byte(val | LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
    i2c_write_byte(val & ~LCD_ENABLE_BIT);
    sleep_us(DELAY_US);
}

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t val, int mode)
{
    uint8_t high = mode | (val & 0xF0) | LCD_BACKLIGHT;
    uint8_t low = mode | ((val << 4) & 0xF0) | LCD_BACKLIGHT;

    i2c_write_byte(high);
    lcd_toggle_enable(high);
    i2c_write_byte(low);
    lcd_toggle_enable(low);
}

void lcd_clear(void)
{
    lcd_send_byte(LCD_CLEAR_DISPLAY, LCD_COMMAND);
}

// go to location on LCD
void lcd_set_cursor(int line, int position)
{
    int val = (line == 0) ? 0x80 + position : 0xC0 + position;
    lcd_send_byte(val, LCD_COMMAND);
}

static void inline lcd_char(char val)
{
    lcd_send_byte(val, LCD_CHARACTER);
}

void lcd_string(const char *s)
{
    while (*s)
    {
        lcd_char(*s++);
    }
}

void lcd_init()
{
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x03, LCD_COMMAND);
    lcd_send_byte(0x02, LCD_COMMAND);

    lcd_send_byte(LCD_ENTRY_MODE_SET | LCD_ENTRY_LEFT, LCD_COMMAND);
    lcd_send_byte(LCD_FUNCTION_SET | LCD_2LINE, LCD_COMMAND);
    lcd_send_byte(LCD_DISPLAY_CONTROL | LCD_DISPLAY_ON, LCD_COMMAND);
    lcd_clear();
}
