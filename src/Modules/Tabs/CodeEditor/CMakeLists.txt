add_library(cremniy_module_code_editor STATIC
    codeeditortab.cpp
    codeeditortab.h
    codeeditorsettings.cpp
    codeeditorsettings.h
    codeeditorsettingspage.cpp
    codeeditorsettingspage.h
)

target_link_libraries(cremniy_module_code_editor
    PUBLIC  cremniy_module_api CodeEditor
    PRIVATE cremniy_warnings cremniy_utils
)
