# ModuleManager is header-only; expose it as an INTERFACE library so it can be
# unit-tested without the rest of the application.
add_library(cremniy_module_manager INTERFACE)
target_include_directories(cremniy_module_manager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_link_libraries(cremniy_module_manager INTERFACE Qt6::Core)

if(BUILD_TESTING)
    qt_add_executable(modulemanagertest tests/modulemanagertest.cpp)
    target_link_libraries(modulemanagertest PRIVATE
        cremniy_module_manager Qt6::Test cremniy_warnings)
    add_test(NAME modulemanagertest COMMAND modulemanagertest)
endif()
