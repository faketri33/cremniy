add_library(cremniy_utils STATIC
    utils.cpp
    utils.h
)
target_include_directories(cremniy_utils PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(cremniy_utils
    PUBLIC  Qt6::Core
    PRIVATE cremniy_warnings
)
