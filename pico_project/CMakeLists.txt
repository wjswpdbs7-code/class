cmake_minimum_required(VERSION 3.13)

if (NOT PICO_SDK_PATH)
	if (DEFINED ENV{PICO_SDK_PATH} AND NOT "$ENV{PICO_SDK_PATH}" STREQUAL "")
		set(PICO_SDK_PATH "$ENV{PICO_SDK_PATH}")
	else()
		set(PICO_SDK_PATH "/home/jjy2026/pico/pico-sdk")
	endif()
endif()

if (NOT PICO_BOARD)
	set(PICO_BOARD pico2_w CACHE STRING "Target board")
endif()

if (PICO_BOARD MATCHES "^pico2")
	set(PICO_PLATFORM rp2350 CACHE STRING "Target platform" FORCE)
endif()

include(pico_sdk_import.cmake)

project(my_project C CXX ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

pico_sdk_init()

set(APP_SOURCE "picomoter.c" CACHE STRING "Application source file")
add_executable(my_project ${APP_SOURCE})
target_link_libraries(my_project pico_stdlib hardware_pwm)
pico_enable_stdio_usb(my_project 1)
pico_enable_stdio_uart(my_project 0)
pico_add_extra_outputs(my_project)