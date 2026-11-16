# Optional developer tooling and build-speed switches (all OFF by default).

option(CREMNIY_ENABLE_PCH "Use precompiled headers for the application shell" OFF)
option(CREMNIY_UNITY_BUILD "Use unity (jumbo) builds for first-party targets" OFF)
option(CREMNIY_ENABLE_CLANG_TIDY "Run clang-tidy (uses the repository .clang-tidy) during the build" OFF)

if(CREMNIY_UNITY_BUILD)
    set(CMAKE_UNITY_BUILD ON)
endif()

if(CREMNIY_ENABLE_CLANG_TIDY)
    find_program(CREMNIY_CLANG_TIDY_EXECUTABLE NAMES clang-tidy REQUIRED)
    set(CMAKE_CXX_CLANG_TIDY "${CREMNIY_CLANG_TIDY_EXECUTABLE}")
endif()
