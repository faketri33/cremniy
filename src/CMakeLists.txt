cmake_minimum_required(VERSION 3.25)

find_package(Git QUIET)

if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_TAG
        OUTPUT_STRIP_TRAILING_WHITESPACE
        ERROR_QUIET
    )

    if(GIT_TAG MATCHES "^v([0-9]+)\\.([0-9]+)\\.([0-9]+)$")
        set(PROJECT_VERSION "${CMAKE_MATCH_1}.${CMAKE_MATCH_2}.${CMAKE_MATCH_3}")
    endif()
endif()

if(NOT PROJECT_VERSION)
    set(PROJECT_VERSION "0.0.0")
endif()

project(cremniy VERSION ${PROJECT_VERSION} LANGUAGES C CXX)

message(STATUS "Cremniy version: ${PROJECT_VERSION}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(Warnings)
include(Sanitizers)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.8.2 REQUIRED COMPONENTS Core Widgets Gui Concurrent LinguistTools Svg Network)
if(BUILD_TESTING)
    find_package(Qt6 6.8.2 REQUIRED COMPONENTS Test)
endif()
# AUTOMOC / AUTOUIC / AUTORCC for every target in the project.
qt_standard_project_setup()

include(Libgit2)

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    main.cpp

    # App
    app/AppContext.h
    app/AppContext.cpp
    app/builtinmodules.h app/builtinmodules.cpp
    app/builtinsettings.h app/builtinsettings.cpp
    app/IDEWindow/idewindow.cpp
    app/IDEWindow/idewindow.h
    app/WelcomeWindow/WelcomeForm/welcome_form.cpp
    app/WelcomeWindow/WelcomeForm/welcome_form.h
    app/WelcomeWindow/RecentProjectsPage/recent_projects_page.cpp
    app/WelcomeWindow/RecentProjectsPage/recent_projects_page.h
    app/WelcomeWindow/CreateProjectPage/create_project_page.cpp
    app/WelcomeWindow/CreateProjectPage/create_project_page.h
    app/WelcomeWindow/ProjectCard/project_card.cpp
    app/WelcomeWindow/ProjectCard/project_card.h

    # Dialogs
    dialogs/filecreatedialog.cpp
    dialogs/filecreatedialog.h
    dialogs/settingsdialog.cpp
    dialogs/settingsdialog.h
    dialogs/pages/generalsettingspage.cpp
    dialogs/pages/generalsettingspage.h
    dialogs/pages/filessettingspage.cpp
    dialogs/pages/filessettingspage.h

    # Widgets
    widgets/clickablelineedit.h
    widgets/filetab.cpp
    widgets/filetab.h
    widgets/filetreepanel.cpp
    widgets/filetreepanel.h
    widgets/terminal/terminalwidget.cpp
    widgets/terminal/terminalwidget.h
    widgets/terminal/terminalpanel.cpp
    widgets/terminal/terminalpanel.h
    ui/FindPanel/findpanel.cpp
    ui/FindPanel/findpanel.h

    # Resources
    resources/cremniy_res.qrc

    # Utils
    utils/utils.h
    utils/utils.cpp
        core/locale/LanguageManager.cpp
        core/locale/LanguageManager.h

    # Core
    core/project/projects_history_manager.cpp
    core/project/projects_history_manager.h

    core/FindEngine/findengine.cpp
    core/FindEngine/findengine.h
    core/FindEngine/findtypes.h

    core/settings/settingspage.h

    core/update/updatechecker.cpp
    core/update/updatechecker.h

    core/icons/iconprovider.cpp
    core/icons/iconprovider.h

    core/settings/exclusionfilterproxymodel.cpp
    core/settings/exclusionfilterproxymodel.h

    core/modules/ModuleManager.h
    core/modules/TabBase.h
    core/modules/WindowBase.h
    core/modules/ReferenceBase.h

    # UI
    ui/FilesTabWidget/filestabwidget.cpp
    ui/FilesTabWidget/filestabwidget.h
    ui/ToolsTabWidget/toolstabwidget.cpp
    ui/ToolsTabWidget/toolstabwidget.h

    # UI Menubar
    ui/MenuBar/menubarbuilder.h ui/MenuBar/menubarbuilder.cpp
    ui/MenuBar/menufactory.h ui/MenuBar/menufactory.cpp
    ui/MenuBar/basemenu.h
    ui/MenuBar/builtinmenus.h ui/MenuBar/builtinmenus.cpp
    dialogs/configurebuild.h dialogs/configurebuild.cpp
    core/project/project_info_manager.h core/project/project_info_manager.cpp

    core/buildman/buildmanager.cpp
    core/buildman/buildmanager.cpp
    widgets/logView/logview.h widgets/logView/logview.cpp


    widgets/buildTab/buildtab.cpp widgets/buildTab/buildtab.h

)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/core/file
    ${CMAKE_CURRENT_SOURCE_DIR}/core/git
    ${CMAKE_CURRENT_SOURCE_DIR}/core/project
    ${CMAKE_CURRENT_SOURCE_DIR}/core/settings
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/ToolsTabWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/FilesTabWidget
    ${CMAKE_CURRENT_SOURCE_DIR}/app/WelcomeWindow/WelcomeForm
    ${CMAKE_CURRENT_SOURCE_DIR}/app/WelcomeWindow/RecentProjectsPage
    ${CMAKE_CURRENT_SOURCE_DIR}/app/WelcomeWindow/CreateProjectPage
    ${CMAKE_CURRENT_SOURCE_DIR}/app/WelcomeWindow/ProjectCard
)

file(GLOB_RECURSE PHOICONS_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/phoicons/*"
)

qt_add_resources(${PROJECT_NAME} "phoicons"
    PREFIX "/icons"
    BASE "resources/icons"
    FILES ${PHOICONS_FILES}
)

# - - Libs - -
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core/file/ ${CMAKE_BINARY_DIR}/core/file/)
target_link_libraries(${PROJECT_NAME} PRIVATE cremniy_file_core)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core/modules/ ${CMAKE_BINARY_DIR}/core/modules/)
target_link_libraries(${PROJECT_NAME} PRIVATE cremniy_module_manager)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core/settings/ ${CMAKE_BINARY_DIR}/core/settings/)
target_link_libraries(${PROJECT_NAME} PRIVATE cremniy_settings_core)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/core/git/ ${CMAKE_BINARY_DIR}/core/git/)
target_link_libraries(${PROJECT_NAME} PRIVATE cremniy_git_core)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/CodeEditor/ ${CMAKE_BINARY_DIR}/libs/CodeEditor/)
target_link_libraries(${PROJECT_NAME} PRIVATE CodeEditor)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/HexEditor/ ${CMAKE_BINARY_DIR}/libs/HexEditor/)
target_link_libraries(${PROJECT_NAME} PRIVATE HexEditor)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/Terminal/ ${CMAKE_BINARY_DIR}/libs/Terminal/)
target_link_libraries(${PROJECT_NAME} PRIVATE cremniy_terminal_core)

# - - Modules - -
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Modules/References/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Modules/Tabs/)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Modules/Windows/)

# - - Menus - -
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui/MenuBar/Menus/)

target_link_libraries(${PROJECT_NAME} PRIVATE
    cremniy_warnings
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
    Qt6::Concurrent
    Qt6::Svg
    Qt6::Network
)

if(NOT WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${HTTP_PARSER_LIB}
        ${PCRE_LIB}
        OpenSSL::SSL
        OpenSSL::Crypto
        ZLIB::ZLIB
    )
endif()

set(APP_LANGUAGES
        en
        ru
)

list(JOIN APP_LANGUAGES ";" APP_LANGUAGES_STR)

configure_file(
        ${CMAKE_SOURCE_DIR}/config.h.in
        ${CMAKE_BINARY_DIR}/config.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_BINARY_DIR}
)

set(TS_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/locale/translations/app_ru.ts
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/locale/translations/qtbase_ru.ts
)

qt6_add_translation(QM_FILES ${TS_FILES})

add_custom_target(translations ALL DEPENDS ${QM_FILES})
add_dependencies(${PROJECT_NAME} translations)

if (APPLE)
    set(TRANSLATIONS_DIR
            "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources/translations"
    )
else ()
    set(TRANSLATIONS_DIR
            "${CMAKE_BINARY_DIR}/Resources/translations"
    )
endif ()

file(MAKE_DIRECTORY ${TRANSLATIONS_DIR})

foreach(QM_FILE ${QM_FILES})
    get_filename_component(QM_FILENAME ${QM_FILE} NAME)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${QM_FILE}"
            "${TRANSLATIONS_DIR}/${QM_FILENAME}"
    )
endforeach()

find_program(WINDEPLOYQT_EXECUTABLE windeployqt)

if(WIN32 AND WINDEPLOYQT_EXECUTABLE)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${WINDEPLOYQT_EXECUTABLE}
                $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Deploying Qt dependencies with windeployqt"
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(APPLE)
    set(ICNS_FILE "${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/cremniy.icns")
    set(MACOSX_BUNDLE_ICON_FILE cremniy.icns)
    set_source_files_properties(${ICNS_FILE} PROPERTIES
        MACOSX_PACKAGE_LOCATION "Resources"
    )
    target_sources(${PROJECT_NAME} PRIVATE ${ICNS_FILE})

    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE cremniy.icns
        MACOSX_BUNDLE_BUNDLE_NAME "Cremniy"
        MACOSX_BUNDLE_GUI_IDENTIFIER "com.mironov.cremniy"
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/Info.plist.in"
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/resources/macos/Assets.car
            $<TARGET_BUNDLE_CONTENT_DIR:${PROJECT_NAME}>/Resources/Assets.car
        COMMENT "Copying prebuilt Tahoe icon asset"
    )
endif()

include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_finalize_executable(${PROJECT_NAME})
