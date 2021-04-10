/*
https://docs.sunfounder.com/projects/thales-kit/en/latest/reading_button_values.html
*/
#include "pico/stdlib.h"

int main()
{
    const uint BUTTON_INPUT = 14;
    const uint ONBOARD_LED = PICO_DEFAULT_LED_PIN;

    gpio_init(ONBOARD_LED);
    gpio_init(BUTTON_INPUT);
    gpio_set_dir(ONBOARD_LED, GPIO_OUT);
    gpio_set_dir(BUTTON_INPUT, GPIO_IN);

    while (true)
    {
        gpio_put(ONBOARD_LED, gpio_get(BUTTON_INPUT) == 0);
    }
}
