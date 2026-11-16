# Public contract for pluggable modules (tabs, windows, references): the base
# classes, ModuleManager and ModuleContext. Every module library links this
# and nothing from the application shell. The base classes are QObjects, so
# the library contains their generated moc code (AUTOMOC) and no hand-written
# translation units.
add_library(cremniy_module_api STATIC
    ModuleContext.h
    ModuleManager.h
    ReferenceBase.h
    TabBase.h
    WindowBase.h
)
target_include_directories(cremniy_module_api PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(cremniy_module_api
    PUBLIC  Qt6::Widgets cremniy_file_core cremniy_settings_core
    PRIVATE cremniy_warnings
)

if(BUILD_TESTING)
    qt_add_executable(modulemanagertest tests/modulemanagertest.cpp)
    target_link_libraries(modulemanagertest PRIVATE
        cremniy_module_api Qt6::Test cremniy_warnings)
    add_test(NAME modulemanagertest COMMAND modulemanagertest)
endif()
