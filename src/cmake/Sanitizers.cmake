# Optional sanitizers, e.g. -DCREMNIY_SANITIZERS="address;undefined".
# Applied directory-wide on purpose: a sanitizer must be enabled consistently
# for every target in the link (including static libraries).

set(CREMNIY_SANITIZERS "" CACHE STRING
    "Semicolon-separated sanitizers to enable (address;undefined;thread)")

if(CREMNIY_SANITIZERS)
    if(MSVC)
        if(CREMNIY_SANITIZERS STREQUAL "address")
            add_compile_options(/fsanitize=address)
        else()
            message(FATAL_ERROR "MSVC supports only CREMNIY_SANITIZERS=address")
        endif()
    else()
        list(JOIN CREMNIY_SANITIZERS "," _cremniy_san)
        add_compile_options(-fsanitize=${_cremniy_san} -fno-omit-frame-pointer)
        add_link_options(-fsanitize=${_cremniy_san})
        unset(_cremniy_san)
    endif()
    message(STATUS "Cremniy sanitizers: ${CREMNIY_SANITIZERS}")
endif()
