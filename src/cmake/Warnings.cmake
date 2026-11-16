# Compiler warnings as a dedicated INTERFACE target.
#
# Link it only to first-party targets so third-party code (libvterm,
# QCodeEditor) is not forced to be warning-clean:
#
#     target_link_libraries(my_target PRIVATE cremniy_warnings)
#
# Set -DCREMNIY_WARNINGS_AS_ERRORS=ON to turn warnings into errors (CI).

option(CREMNIY_WARNINGS_AS_ERRORS "Treat compiler warnings as errors" OFF)

add_library(cremniy_warnings INTERFACE)

if(MSVC)
    target_compile_options(cremniy_warnings INTERFACE /W4)
    if(CREMNIY_WARNINGS_AS_ERRORS)
        target_compile_options(cremniy_warnings INTERFACE /WX)
    endif()
else()
    target_compile_options(cremniy_warnings INTERFACE -Wall -Wextra -Wpedantic)
    if(CREMNIY_WARNINGS_AS_ERRORS)
        target_compile_options(cremniy_warnings INTERFACE -Werror)
    endif()
endif()
