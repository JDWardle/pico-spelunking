/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <string.h>
#include "math.h"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "i2c/lcd.h"

const uint DHT_PIN = 15;
const uint MAX_TIMINGS = 85;


typedef struct {
    float humidity;
    float temp_celsius;
} dht_reading;

void read_from_dht(dht_reading *result);
bool equal_float_tolerance(float a, float b);

int main()
{
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
#warning i2c/lcd_1602_i2c example requires a board with I2C pins
#else
    // This example will use I2C0 on the default SDA and SCL pins (4, 5 on a Pico)
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    // Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));

    gpio_init(DHT_PIN);

    lcd_init();

    float humidity;
    float temperature;

    while(1)
    {
        dht_reading reading;
        read_from_dht(&reading);

        // Only update the LCD screen if either of the readings have changed.
        if (equal_float_tolerance(humidity, reading.humidity) && equal_float_tolerance(temperature, reading.temp_celsius))
        {
            continue;
        }

        humidity = reading.humidity;
        temperature = reading.temp_celsius;

        float farhenheit = (temperature * 9) / 5 + 32;

        char temp_msg[14];
        char humidity_msg[6];
        sprintf(temp_msg, "%.1fC (%.1fF)", reading.temp_celsius, farhenheit);
        sprintf(humidity_msg, "%.1f%%", reading.humidity);


        lcd_set_cursor(0, (MAX_CHARS / 2) - strlen(humidity_msg) / 2);
        lcd_string(humidity_msg);

        lcd_set_cursor(1, (MAX_CHARS / 2) - strlen(temp_msg) / 2);
        lcd_string(temp_msg);

        sleep_ms(2000);
    }

    return 0;
#endif
}

// Took this from here https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
bool equal_float_tolerance(float a, float b)
{
    float diff = fabs(a - b);
    a = fabs(a);
    b = fabs(b);

    float largest = (b > a) ? b : a;

    return diff <= largest * __FLT_EPSILON__;
}

// This is some black magic, pulled examples from the Pico C/C++ PDF and these projects:
// https://github.com/carolinedunn/pico-weather-station/blob/main/weatherstation.c
// https://github.com/adafruit/DHT-sensor-library/blob/master/DHT.cpp
void read_from_dht(dht_reading *result)
{
int data[5] = {0, 0, 0, 0, 0};
    uint last = 1;
    uint j = 0;

    gpio_set_dir(DHT_PIN, GPIO_OUT);
    gpio_put(DHT_PIN, 0);
    sleep_ms(20);
    gpio_set_dir(DHT_PIN, GPIO_IN);

    for (uint i = 0; i < MAX_TIMINGS; i++) {
        uint count = 0;
        while (gpio_get(DHT_PIN) == last) {
            count++;
            sleep_us(1);
            if (count == 255) {
                break;
            }
        }
        last = gpio_get(DHT_PIN);

        if (count == 255) {
            break;
        }

        if ((i >= 4) && (i % 2 == 0)) {
            data[j / 8] <<= 1;
            // Pico docs say 16, but that always gives bad data. One example has 46 which works.
            // Experimented with other values and just ended up on 20 since that was the last one
            // I used that still worked.
            if (count > 20) {
                data[j / 8] |= 1;
            }
            j++;
        }
    }

    if ((j >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))) {
        result->humidity = (float) ((data[0] << 8) + data[1]) / 10;
        if (result->humidity > 100) {
            result->humidity = data[0];
        }

        result->temp_celsius = (float) (((data[2] & 0x7F) << 8) + data[3]) / 10;
        if (result->temp_celsius > 125) {
            result->temp_celsius = data[2];
        }

        if (data[2] & 0x80) {
            result->temp_celsius = -result->temp_celsius;
        }
    } else {
        printf("Bad data\n");
    }
}
