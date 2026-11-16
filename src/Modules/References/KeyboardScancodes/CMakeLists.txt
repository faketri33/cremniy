add_library(cremniy_module_keyboard_scancodes STATIC
    keyboardscancodesref.cpp
    keyboardscancodesref.h
    keyboardscancodevizwidget.cpp
    keyboardscancodevizwidget.h
)

target_link_libraries(cremniy_module_keyboard_scancodes
    PUBLIC  cremniy_module_api
    PRIVATE cremniy_warnings
)
