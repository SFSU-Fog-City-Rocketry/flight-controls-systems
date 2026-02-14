# FILE(GLOB_RECURSE app_sources ${CMAKE_SOURCE_DIR}/applications/*.*)

set(PROJECT_DIR ${CMAKE_CURRENT_LIST_DIR}/../)

set(
    app_sources
    main.cpp

    ${PROJECT_DIR}/src/drivers/esp32/output_pin.cpp
    ${PROJECT_DIR}/src/drivers/esp32/input_pin.cpp
    ${PROJECT_DIR}/src/drivers/esp32/utils.cpp
    ${PROJECT_DIR}/src/drivers/esp32/serial.cpp
)

idf_component_register(
    SRCS ${app_sources}
    INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/../drivers
)
