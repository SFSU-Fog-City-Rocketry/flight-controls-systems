# Copyright 2024 Khalil Estell
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.25)
if(DEFINED ENV{PICO_SDK_PATH})
    set(PICO_CXX_ENABLE_EXCEPTIONS 1)
    # set(PICO_CLIB picolibc)
    set(CMAKE_ASM_FLAGS_INIT "-mcpu=cortex-m0")
    include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif()

project(demo LANGUAGES CXX C ASM)
set(CMAKE_EXECUTABLE_SUFFIX .elf)
if("$ENV{LIBHAL_PLATFORM_LIBRARY}" STREQUAL "")
    message(
        FATAL_ERROR
        "Build environment variable LIBHAL_PLATFORM_LIBRARY is required for "
        "this project."
    )
endif()
if("$ENV{LIBHAL_PLATFORM}" STREQUAL "")
    message(
        FATAL_ERROR
        "Build environment variable LIBHAL_PLATFORM is required for "
        "this project."
    )
endif()

find_package(libhal-$ENV{LIBHAL_PLATFORM_LIBRARY} REQUIRED CONFIG)
find_package(libhal-util REQUIRED CONFIG)
#find_package(mp-units REQUIRED)

pico_sdk_init()

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE hardware_adc hardware_dma hardware_pwm hardware_spi libhal::util libhal::picosdk pico_stdlib
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_add_extra_outputs(${PROJECT_NAME})

