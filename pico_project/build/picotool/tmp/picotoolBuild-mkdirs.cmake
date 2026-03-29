# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/jjy2026/pico_project/build/_deps/picotool-src"
  "/home/jjy2026/pico_project/build/_deps/picotool-build"
  "/home/jjy2026/pico_project/build/_deps"
  "/home/jjy2026/pico_project/build/picotool/tmp"
  "/home/jjy2026/pico_project/build/picotool/src/picotoolBuild-stamp"
  "/home/jjy2026/pico_project/build/picotool/src"
  "/home/jjy2026/pico_project/build/picotool/src/picotoolBuild-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/jjy2026/pico_project/build/picotool/src/picotoolBuild-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/jjy2026/pico_project/build/picotool/src/picotoolBuild-stamp${cfgdir}") # cfgdir has leading slash
endif()
