# Provides the INTERFACE target `cremniy_libgit2` carrying libgit2 and the
# system libraries its static builds need.
#
# libgit2 ships a CMake package on some platforms and only a pkg-config file or
# plain headers/libraries on others. All three layouts are supported so
# developers do not have to pass platform-specific paths to CMake.

get_filename_component(_cremniy_compiler_bin_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)
get_filename_component(_cremniy_toolchain_prefix "${_cremniy_compiler_bin_dir}" DIRECTORY)
set(_cremniy_libgit2_hints
    "$ENV{LIBGIT2_ROOT}"
    "$ENV{MINGW_PREFIX}"
    "${_cremniy_toolchain_prefix}"
    "$ENV{HOMEBREW_PREFIX}/opt/libgit2"
    "/opt/homebrew/opt/libgit2"
    "/usr/local/opt/libgit2"
)
list(FILTER _cremniy_libgit2_hints EXCLUDE REGEX "^$")

set(_cremniy_libgit2_target "")
set(_cremniy_libgit2_include_dirs "")

find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(LIBGIT2 QUIET IMPORTED_TARGET libgit2)
    if(TARGET PkgConfig::LIBGIT2)
        set(_cremniy_libgit2_target PkgConfig::LIBGIT2)
    endif()
endif()

if(NOT _cremniy_libgit2_target)
    find_package(libgit2 CONFIG QUIET HINTS ${_cremniy_libgit2_hints})
    if(TARGET libgit2::libgit2package)
        set(_cremniy_libgit2_target libgit2::libgit2package)
    elseif(TARGET libgit2::libgit2)
        set(_cremniy_libgit2_target libgit2::libgit2)
    endif()
endif()

if(NOT _cremniy_libgit2_target)
    find_path(LIBGIT2_INCLUDE_DIR
        NAMES git2.h
        HINTS ${_cremniy_libgit2_hints}
        PATH_SUFFIXES include
    )
    find_library(LIBGIT2_LIBRARY
        NAMES git2 libgit2
        HINTS ${_cremniy_libgit2_hints}
        PATH_SUFFIXES lib lib64
    )
    if(NOT LIBGIT2_INCLUDE_DIR OR NOT LIBGIT2_LIBRARY)
        message(FATAL_ERROR
            "libgit2 was not found. Install the libgit2 development package "
            "or set LIBGIT2_ROOT to its installation prefix."
        )
    endif()
    set(_cremniy_libgit2_target "${LIBGIT2_LIBRARY}")
    set(_cremniy_libgit2_include_dirs "${LIBGIT2_INCLUDE_DIR}")
endif()

add_library(cremniy_libgit2 INTERFACE)
target_link_libraries(cremniy_libgit2 INTERFACE ${_cremniy_libgit2_target})
if(_cremniy_libgit2_include_dirs)
    target_include_directories(cremniy_libgit2 SYSTEM INTERFACE ${_cremniy_libgit2_include_dirs})
endif()

# System libraries needed when libgit2 is linked statically on Unix-likes.
if(NOT WIN32)
    find_package(ZLIB REQUIRED)
    find_package(OpenSSL REQUIRED)
    find_library(PCRE_LIB NAMES pcre pcre2-8)
    find_library(HTTP_PARSER_LIB NAMES http_parser REQUIRED)
    target_link_libraries(cremniy_libgit2 INTERFACE
        ${HTTP_PARSER_LIB}
        OpenSSL::SSL
        OpenSSL::Crypto
        ZLIB::ZLIB
    )
    if(PCRE_LIB)
        target_link_libraries(cremniy_libgit2 INTERFACE ${PCRE_LIB})
    endif()
endif()
