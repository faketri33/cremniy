add_library(cremniy_module_data_converter STATIC
    dataconverterdialog.cpp
    dataconverterdialog.h
)

target_link_libraries(cremniy_module_data_converter
    PUBLIC  cremniy_module_api
    PRIVATE cremniy_warnings
)
