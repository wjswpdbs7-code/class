// src/main.c
// Default application entry for pico_project.
// Add reusable source files under src/modules/*.c and they will be auto-included by CMake.

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define MODE_SERVO 1
#define MODE_DC 2

#ifndef MOTOR_MODE
#define MOTOR_MODE MODE_SERVO
#endif

#if MOTOR_MODE == MODE_SERVO
#define SERVO_PIN 15
#define SERVO_CLKDIV 125.0f
#define SERVO_WRAP (20000 - 1)
#define SERVO_MIN 1000
#define SERVO_MID 1500
#define SERVO_MAX 2000
#else
#define DC_PWM_PIN 15
#define DC_DIR_PIN_A 16
#define DC_DIR_PIN_B 17
#define DC_PWM_WRAP 65535
#endif

int main()
{
    stdio_init_all();
    sleep_ms(200);

#if MOTOR_MODE == MODE_SERVO
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint chan = pwm_gpio_to_channel(SERVO_PIN);

    pwm_set_clkdiv(slice, SERVO_CLKDIV);
    pwm_set_wrap(slice, SERVO_WRAP);
    pwm_set_chan_level(slice, chan, SERVO_MAX);
    pwm_set_enabled(slice, 1);

    while (1)
    {
        tight_loop_contents();
    }
#else
    gpio_init(DC_DIR_PIN_A);
    gpio_init(DC_DIR_PIN_B);
    gpio_set_dir(DC_DIR_PIN_A, GPIO_OUT);
    gpio_set_dir(DC_DIR_PIN_B, GPIO_OUT);
    gpio_put(DC_DIR_PIN_A, 1);
    gpio_put(DC_DIR_PIN_B, 0);

    gpio_set_function(DC_PWM_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(DC_PWM_PIN);
    pwm_set_wrap(slice, DC_PWM_WRAP);
    pwm_set_chan_level(slice, pwm_gpio_to_channel(DC_PWM_PIN), DC_PWM_WRAP / 2);
    pwm_set_enabled(slice, 1);

    while (1)
    {
        tight_loop_contents();
    }
#endif

    return 0;
}
