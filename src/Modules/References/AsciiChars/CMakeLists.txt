add_library(cremniy_module_ascii_chars STATIC
    asciicharsref.cpp
    asciicharsref.h
)

target_link_libraries(cremniy_module_ascii_chars
    PUBLIC  cremniy_module_api
    PRIVATE cremniy_warnings
)
