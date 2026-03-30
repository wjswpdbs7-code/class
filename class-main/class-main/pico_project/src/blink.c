/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"//라이브러리 인식이 안되면 이 부분을 #include "pico/pico.h"로 바꿔보세요

// Pico W devices use a GPIO on the WIFI chip for the LED,
// so when building for Pico W, CYW43_WL_GPIO_LED_PIN will be defined
#ifdef CYW43_WL_GPIO_LED_PIN
#if __has_include("pico/cyw43_arch.h")
#include "pico/cyw43_arch.h"
#define HAS_CYW43_ARCH 1
#endif
#endif

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 250
#endif

// Perform initialisation
int pico_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // A device like Pico that uses a GPIO for the LED will define PICO_DEFAULT_LED_PIN
    // so we can use normal GPIO functionality to turn the led on and off
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN) && defined(HAS_CYW43_ARCH)
    // For Pico W devices we need to initialise the driver etc
    return cyw43_arch_init();
#endif
    return PICO_ERROR_GENERIC;
}

// Turn the led on or off
void pico_set_led(int led_on) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Just set the GPIO on or off
    gpio_put(PICO_DEFAULT_LED_PIN, led_on);
#elif defined(CYW43_WL_GPIO_LED_PIN) && defined(HAS_CYW43_ARCH)
    // Ask the wifi "driver" to set the GPIO on or off
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, led_on);
#endif
}

int main() {
    int rc = pico_led_init();
    hard_assert(rc == PICO_OK);
    while (1) {
        pico_set_led(1);
        sleep_ms(LED_DELAY_MS);
        pico_set_led(0);
        sleep_ms(LED_DELAY_MS);
    }
}
/// 이 코드는 Raspberry Pi Pico (또는 Pico W)에서 LED를 깜빡이게 하는 예제입니다.
// 보드에 코드를 업로드하면 LED가 250ms 간격으로 켜졌다 꺼졌다 반복됩니다.