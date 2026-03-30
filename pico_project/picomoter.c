// picomoter.c
// DF9GMS 모터를 Raspberry Pi Pico (Pico W 계열)에서 부팅 시 자동으로 구동하는 예제
// 사용 전 연결:
// - 서보(signal) 방식(3핀): VCC(5V), GND, SIGNAL -> SIGNAL을 아래 지정한 GPIO에 연결
// - DC 모터(드라이버 사용): DIR1, DIR2, PWM(속도) 핀을 드라이버에 연결
// 전원: 모터는 보드 5V 핀 대신 별도 전원(권장)을 사용하세요. 접지(GND)는 공통으로 연결해야 합니다.

#include "pico/stdlib.h"
#include "hardware/pwm.h"

// 설정: 필요에 맞게 수정
// MODE_SERVO: 서보(또는 continuous-servo) 신호를 사용
// MODE_DC: H-bridge 등 드라이버를 통해 DC 모터 제어
#define MODE_SERVO 1
#define MODE_DC 2

// 기본 모드 (필요하면 build 시 -DMOTOR_MODE=MODE_DC 로 변경)
#ifndef MOTOR_MODE
#define MOTOR_MODE MODE_SERVO
#endif

// 핀 설정 (보드 연결에 맞게 변경)
#if MOTOR_MODE == MODE_SERVO
#define SERVO_PIN 15 // 서보 제어 신호를 연결한 GPIO
// 서보: 50Hz(20ms) 주기, 펄스 폭 1000..2000us
#define SERVO_CLKDIV 125.0f
#define SERVO_WRAP (20000 - 1) // 1us 단위로 20ms
#define SERVO_MIN 1000
#define SERVO_MID 1500
#define SERVO_MAX 2000

#else                   // MODE_DC
#define DC_PWM_PIN 15   // PWM으로 속도 제어
#define DC_DIR_PIN_A 16 // 방향 제어 핀 A
#define DC_DIR_PIN_B 17 // 방향 제어 핀 B
#define DC_PWM_WRAP 65535
#endif

int main()
{
    stdio_init_all();
    sleep_ms(200); // 안정화

#if MOTOR_MODE == MODE_SERVO
    // 서보용 PWM 설정
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(SERVO_PIN);
    uint chan = pwm_gpio_to_channel(SERVO_PIN);

    pwm_set_clkdiv(slice, SERVO_CLKDIV);
    pwm_set_wrap(slice, SERVO_WRAP);

    // 즉시 동작: continuous 서보라면 MID에서 약간 앞(속도)로 이동
    // DF9GMS가 연속회전 서보라면 MID(정지)에서 MIN/MAX로 속도 제어
    // 여기서는 시연으로 전진(2000us 펄스)
    uint16_t level = SERVO_MAX; // 2000us
    pwm_set_chan_level(slice, chan, level);
    pwm_set_enabled(slice, true);

    // 계속 동작
    while (true)
    {
        // 필요 시 속도/방향 제어 코드 추가 가능
        tight_loop_contents();
    }

#else
    // DC 모터 제어: DIR(A/B)과 PWM
    gpio_init(DC_DIR_PIN_A);
    gpio_init(DC_DIR_PIN_B);
    gpio_set_dir(DC_DIR_PIN_A, GPIO_OUT);
    gpio_set_dir(DC_DIR_PIN_B, GPIO_OUT);
    // 초기 방향: A=1, B=0
    gpio_put(DC_DIR_PIN_A, 1);
    gpio_put(DC_DIR_PIN_B, 0);

    // PWM 설정
    gpio_set_function(DC_PWM_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(DC_PWM_PIN);
    pwm_set_wrap(slice, DC_PWM_WRAP);
    pwm_set_chan_level(slice, pwm_gpio_to_channel(DC_PWM_PIN), DC_PWM_WRAP / 2); // 50% 속도
    pwm_set_enabled(slice, true);

    while (true)
    {
        tight_loop_contents();
    }
#endif

    return 0;
}
// 핀연결은 다음과 같이 하세요:
//  df9gms 모터의 경우:
// 색깔별로 - 빨강: VCC(5V), 검정: GND, 노랑(또는 흰색): SIGNAL
// 보드위 핀의 위치는  GPIO 번호로 연결하세요. 예를 들어, SIGNAL을 GPIO 15에 연결하면 위 코드에서 SERVO_PIN을 15로 설정합니다.

// CMake 빌드는 루트 CMakeLists.txt의 APP_SOURCE 설정으로 이 파일이 자동 포함됩니다.