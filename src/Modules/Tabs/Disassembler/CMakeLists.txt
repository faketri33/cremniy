add_library(cremniy_module_disassembler STATIC
    disassemblertab.cpp
    disassemblertab.h
    disassemblersettings.cpp
    disassemblersettings.h
    disassemblersettingspage.cpp
    disassemblersettingspage.h
    disassemblerworker.cpp
    disassemblerworker.h
    disasm/disasmsyntaxdelegate.cpp
    disasm/disasmsyntaxdelegate.h
    disasm/disasmtexthighlighter.cpp
    disasm/disasmtexthighlighter.h
    disasm/backends/radare2backend.cpp
    disasm/backends/radare2backend.h
    instructionhelpservice.cpp
    instructionhelpservice.h
)

target_include_directories(cremniy_module_disassembler PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(cremniy_module_disassembler
    PUBLIC  cremniy_module_api
    PRIVATE cremniy_warnings
)
