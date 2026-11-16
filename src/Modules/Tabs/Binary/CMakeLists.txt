add_library(cremniy_module_binary STATIC
    binarytab.cpp
    binarytab.h
    formatpage.cpp
    formatpage.h
    formatpagefactory.cpp
    formatpagefactory.h
    FormatPages/RAW/rawpage.cpp
    FormatPages/RAW/rawpage.h
    FormatPages/ELF/elfpage.cpp
    FormatPages/ELF/elfpage.h
    FormatPages/PE/pepage.cpp
    FormatPages/PE/pepage.h
    FormatPages/MBR/mbrpage.cpp
    FormatPages/MBR/mbrpage.h
)

target_include_directories(cremniy_module_binary PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/FormatPages/RAW
    ${CMAKE_CURRENT_SOURCE_DIR}/FormatPages/ELF
    ${CMAKE_CURRENT_SOURCE_DIR}/FormatPages/PE
    ${CMAKE_CURRENT_SOURCE_DIR}/FormatPages/MBR
)

target_link_libraries(cremniy_module_binary
    PUBLIC  cremniy_module_api
    PRIVATE cremniy_warnings HexEditor
)
