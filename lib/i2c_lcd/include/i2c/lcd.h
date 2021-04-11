/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _I2C_LCD_H
#define _I2C_LCD_H

#include <stdint.h>

// commands
#define LCD_CLEAR_DISPLAY 0x01
#define LCD_RETURN_HOME 0x02
#define LCD_ENTRY_MODE_SET 0x04
#define LCD_DISPLAY_CONTROL 0x08
#define LCD_CURSOR_SHIFT 0x10
#define LCD_FUNCTION_SET 0x20
#define LCD_SET_CGRAM_ADDR 0x40
#define LCD_SET_DDRAM_ADDR 0x80

// flags for display entry mode
#define LCD_ENTRY_SHIFT_INCREMENT 0x01
#define LCD_ENTRY_LEFT 0x02

// flags for display and cursor control
#define LCD_BLINK_ON 0x01
#define LCD_CURSOR_ON 0x02
#define LCD_DISPLAY_ON 0x04

// flags for display and cursor shift
#define LCD_MOVE_RIGHT 0x04
#define LCD_DISPLAY_MOVE 0x08

// flags for function set
#define LCD_5x10_DOTS 0x04
#define LCD_2LINE 0x08
#define LCD_8BIT_MODE 0x10

// flag for backlight control
#define LCD_BACKLIGHT 0x08

#define LCD_ENABLE_BIT 0x04

// By default these LCD display drivers are on bus address 0x27
static int DEFAULT_LCD_ADDR = 0x27;

// Modes for lcd_send_byte
#define LCD_CHARACTER 1
#define LCD_COMMAND 0

#define MAX_LINES 2
#define MAX_CHARS 16

/* Quick helper function for single byte transfers */
void i2c_write_byte(uint8_t val);

#define DELAY_US 600
void lcd_toggle_enable(uint8_t val);

// The display is sent a byte as two separate nibble transfers
void lcd_send_byte(uint8_t val, int mode);

void lcd_clear(void);

// go to location on LCD
void lcd_set_cursor(int line, int position);

static void inline lcd_char(char val);

void lcd_string(const char *s);

void lcd_init();
#endif
