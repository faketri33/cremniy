# Pure logic (Qt Core only) lives in its own library so it can be unit-tested
# without the GUI.
add_library(cremniy_reverse_calculator_engine STATIC
    reversecalculatorengine.cpp
    reversecalculatorengine.h
)
target_include_directories(cremniy_reverse_calculator_engine
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
)
target_link_libraries(cremniy_reverse_calculator_engine
    PUBLIC  Qt6::Core
    PRIVATE cremniy_warnings
)

add_library(cremniy_module_reverse_calculator STATIC
    reversecalculatordialog.cpp
    reversecalculatordialog.h
)
target_link_libraries(cremniy_module_reverse_calculator
    PUBLIC  cremniy_module_api
    PRIVATE cremniy_warnings cremniy_reverse_calculator_engine
)

if(BUILD_TESTING)
    qt_add_executable(reversecalculatorenginetest tests/reversecalculatorenginetest.cpp)
    target_link_libraries(reversecalculatorenginetest PRIVATE
        cremniy_reverse_calculator_engine Qt6::Test)
    add_test(NAME reversecalculatorenginetest COMMAND reversecalculatorenginetest)
endif()
