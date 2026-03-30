cmake_minimum_required(VERSION 3.10)
project(pico_project)

set(CMAKE_CXX_STANDARD 17)
include(ExternalProject)

# --- auto-managed subdirectories block BEGIN ---
# The following block is maintained by scripts/update_cmakelists.py
# Do not edit the lines between BEGIN and END by hand; they will be replaced.
# If you want to add a manual subdirectory, place it outside this block.
# AUTO_SUBDIRS_BEGIN
# AUTO_SUBDIRS_END
# --- auto-managed subdirectories block END ---

ExternalProject_Add(atmega128_project
	SOURCE_DIR ${CMAKE_SOURCE_DIR}/atmega128
	BINARY_DIR ${CMAKE_BINARY_DIR}/atmega128-build
	CMAKE_ARGS
		-DCMAKE_TOOLCHAIN_FILE=${CMAKE_SOURCE_DIR}/atmega128/avr-toolchain.cmake
		-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
		-DCMAKE_EXPORT_COMPILE_COMMANDS=ON
	INSTALL_COMMAND ""
)