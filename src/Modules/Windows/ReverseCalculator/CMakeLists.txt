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

target_sources(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/reversecalculatordialog.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/reversecalculatordialog.h
)
target_link_libraries(${PROJECT_NAME} PRIVATE cremniy_reverse_calculator_engine)

if(BUILD_TESTING)
    qt_add_executable(reversecalculatorenginetest tests/reversecalculatorenginetest.cpp)
    target_link_libraries(reversecalculatorenginetest PRIVATE
        cremniy_reverse_calculator_engine Qt6::Test)
    add_test(NAME reversecalculatorenginetest COMMAND reversecalculatorenginetest)
endif()
