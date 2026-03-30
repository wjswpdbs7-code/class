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

# Some Linux distributions place newlib specs outside GCC's default lookup path.
# Add the newlib directory as a GCC search prefix so `--specs=nosys.specs` resolves.
if (EXISTS "/usr/lib/arm-none-eabi/newlib/nosys.specs")
	add_link_options(-B/usr/lib/arm-none-eabi/newlib)
endif()

if (EXISTS "/usr/include/newlib/assert.h")
	include_directories(SYSTEM /usr/include/newlib)
endif()

pico_sdk_init()

file(GLOB APP_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_LIST_DIR}/src/*.c"
)
set(APP_EXTRA_SOURCES)
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/motor2.c")
	list(APPEND APP_EXTRA_SOURCES "${CMAKE_CURRENT_LIST_DIR}/motor2.c")
endif()
list(APPEND APP_SOURCES ${APP_EXTRA_SOURCES})

file(GLOB APP_MODULE_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_LIST_DIR}/src/modules/*.c"
)

foreach(APP_SOURCE IN LISTS APP_SOURCES)
	get_filename_component(APP_NAME "${APP_SOURCE}" NAME_WE)

	add_executable(${APP_NAME}
		${APP_SOURCE}
		${APP_MODULE_SOURCES}
	)
	target_link_libraries(${APP_NAME} pico_stdlib hardware_pwm)
	if (TARGET pico_cyw43_arch_none)
		target_link_libraries(${APP_NAME} pico_cyw43_arch_none)
	endif()
	pico_enable_stdio_usb(${APP_NAME} 1)
	pico_enable_stdio_uart(${APP_NAME} 0)
	pico_add_extra_outputs(${APP_NAME})
endforeach()

# Editor indexing target: include standalone files under src/ in compile_commands.json
# so IntelliSense can resolve Pico headers even before a file is wired into an app target.
file(GLOB APP_INDEX_SOURCES CONFIGURE_DEPENDS
	"${CMAKE_CURRENT_LIST_DIR}/src/*.c"
	"${CMAKE_CURRENT_LIST_DIR}/src/modules/*.c"
)
if (EXISTS "${CMAKE_CURRENT_LIST_DIR}/motor2.c")
	list(APPEND APP_INDEX_SOURCES "${CMAKE_CURRENT_LIST_DIR}/motor2.c")
endif()
add_library(editor_index OBJECT EXCLUDE_FROM_ALL ${APP_INDEX_SOURCES})
target_link_libraries(editor_index PRIVATE pico_stdlib hardware_pwm)
if (TARGET pico_cyw43_arch_none)
	target_link_libraries(editor_index PRIVATE pico_cyw43_arch_none)
endif()
target_include_directories(editor_index SYSTEM PRIVATE
	"/home/jjy2026/pico/pico-sdk/src/rp2_common/pico_cyw43_arch/include"
)