add_library(cremniy_module_shellcode_generator STATIC
    shellcodeengine.cpp
    shellcodeengine.h
    shellcodegeneratordialog.cpp
    shellcodegeneratordialog.h
)

target_link_libraries(cremniy_module_shellcode_generator
    PUBLIC  cremniy_module_api
    PRIVATE cremniy_warnings CodeEditor
)
