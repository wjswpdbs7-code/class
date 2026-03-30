#include <stdio.h>
#include "pico/stdlib.h"
int main() {
    stdio_init_all();
    while (true) {
        printf("Hello, Pico!\n");
        sleep_ms(1000);
    }
}

//이 코드는 Raspberry Pi Pico 보드에서 실행되는 간단한 C 프로그램입니다. 
//프로그램은 무한 루프를 사용하여 매초마다 "Hello, Pico!"라는 메시지를 출력합니다.
//출력되는 메시지는 시리얼 콘솔에서 확인할 수 있습니다.
//시리얼 콘솔은 Raspberry Pi Pico 보드와 컴퓨터를 USB 케이블로 연결한 후, 터미널 프로그램을 사용하여 접근할 수 있습니다.
//시리얼 콘설에 출력하는 통신방식은 USB CDC (Communications Device Class)로, Raspberry Pi Pico 보드가 USB를 통해 시리얼 통신을 할 수 있도록 지원하는 방식입니다.
