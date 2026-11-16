add_library(cremniy_module_stm32_pinout STATIC
    stm32pinout.cpp
    stm32pinout.h
)

target_include_directories(cremniy_module_stm32_pinout PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cremniy_module_stm32_pinout
    PUBLIC  cremniy_module_api
    PRIVATE cremniy_warnings
)
