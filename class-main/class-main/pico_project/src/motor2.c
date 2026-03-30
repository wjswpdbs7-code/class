#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// Change this to your actual signal pin.
#define SERVO_PIN 15

// 50 Hz servo signal: 20,000 us period.
#define SERVO_CLKDIV 125.0f
#define SERVO_WRAP 19999

// Pulse width range for 0..180 deg (safe range for many servos).
#define SERVO_MIN_US 1000
#define SERVO_MAX_US 2000

#define STEP_DEG 120
#define MOVE_WAIT_MS 900

static int clamp_int(int v, int lo, int hi)
{
	if (v < lo) return lo;
	if (v > hi) return hi;
	return v;
}

static uint16_t angle_to_level_us(int angle_deg)
{
	int a = clamp_int(angle_deg, 0, 180);
	int pulse = SERVO_MIN_US + ((SERVO_MAX_US - SERVO_MIN_US) * a) / 180;
	return (uint16_t)pulse;
}

static void servo_write_angle(uint slice, uint chan, int angle_deg)
{
	pwm_set_chan_level(slice, chan, angle_to_level_us(angle_deg));
}

int main(void)
{
	stdio_init_all();

	gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
	uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
	uint chan = pwm_gpio_to_channel(SERVO_PIN);

	pwm_set_clkdiv(slice, SERVO_CLKDIV);
	pwm_set_wrap(slice, SERVO_WRAP);
	pwm_set_enabled(slice, true);

	// Start from center.
	int current_angle = 90;
	servo_write_angle(slice, chan, current_angle);

	sleep_ms(1000);
	printf("Servo ready on GPIO %d\n", SERVO_PIN);
	printf("Input '1' = CCW +120 deg, '2' = CW -120 deg\n");

	while (true)
	{
		int ch = getchar_timeout_us(0);
		if (ch == PICO_ERROR_TIMEOUT)
		{
			tight_loop_contents();
			continue;
		}

		if (ch == '1')
		{
			int target = clamp_int(current_angle + STEP_DEG, 0, 180);
			printf("1 received: %d -> %d deg (CCW)\n", current_angle, target);
			servo_write_angle(slice, chan, target);
			sleep_ms(MOVE_WAIT_MS);
			current_angle = target;
			printf("Stopped at %d deg\n", current_angle);
		}
		else if (ch == '2')
		{
			int target = clamp_int(current_angle - STEP_DEG, 0, 180);
			printf("2 received: %d -> %d deg (CW)\n", current_angle, target);
			servo_write_angle(slice, chan, target);
			sleep_ms(MOVE_WAIT_MS);
			current_angle = target;
			printf("Stopped at %d deg\n", current_angle);
		}
	}
}
