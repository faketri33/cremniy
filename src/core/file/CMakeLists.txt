add_library(cremniy_file_core STATIC
    FileDataBuffer.cpp
    FileDataBuffer.h
    filecontext.h
    filemanager.cpp
    filemanager.h
)

# Headers are included as "core/file/<name>.h", rooted at src/.
target_include_directories(cremniy_file_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../..)
target_link_libraries(cremniy_file_core
    PUBLIC  Qt6::Core
    PRIVATE cremniy_warnings
)
