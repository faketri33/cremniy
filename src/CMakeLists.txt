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
include(Tooling)

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

# Generated config.h (version, supported languages).
set(APP_LANGUAGES en ru)
list(JOIN APP_LANGUAGES ";" APP_LANGUAGES_STR)
configure_file(
    ${PROJECT_SOURCE_DIR}/config.h.in
    ${PROJECT_BINARY_DIR}/generated/config.h
)
add_library(cremniy_config INTERFACE)
target_include_directories(cremniy_config INTERFACE ${PROJECT_BINARY_DIR}/generated)

# - - Libraries - -
add_subdirectory(utils)
add_subdirectory(core/file)
add_subdirectory(core/settings)
add_subdirectory(core/git)
add_subdirectory(core/modules)
add_subdirectory(libs/CodeEditor)
add_subdirectory(libs/HexEditor)
add_subdirectory(libs/Terminal)

# - - Modules (one library each) - -
add_subdirectory(Modules/References)
add_subdirectory(Modules/Tabs)
add_subdirectory(Modules/Windows)

# - - Application shell: windows, panels, menus, composition root - -
add_library(cremniy_shell STATIC
    # Composition root
    app/AppContext.cpp
    app/AppContext.h
    app/builtinmodules.cpp
    app/builtinmodules.h
    app/builtinsettings.cpp
    app/builtinsettings.h

    # Windows
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
    dialogs/configurebuild.cpp
    dialogs/configurebuild.h
    dialogs/filecreatedialog.cpp
    dialogs/filecreatedialog.h
    dialogs/settingsdialog.cpp
    dialogs/settingsdialog.h
    dialogs/pages/filessettingspage.cpp
    dialogs/pages/filessettingspage.h
    dialogs/pages/generalsettingspage.cpp
    dialogs/pages/generalsettingspage.h

    # Widgets
    widgets/buildTab/buildtab.cpp
    widgets/buildTab/buildtab.h
    widgets/clickablelineedit.h
    widgets/filetab.cpp
    widgets/filetab.h
    widgets/filetreepanel.cpp
    widgets/filetreepanel.h
    widgets/logView/logview.cpp
    widgets/logView/logview.h
    widgets/terminal/terminalpanel.cpp
    widgets/terminal/terminalpanel.h
    widgets/terminal/terminalwidget.cpp
    widgets/terminal/terminalwidget.h

    # UI
    ui/FilesTabWidget/filestabwidget.cpp
    ui/FilesTabWidget/filestabwidget.h
    ui/FindPanel/findpanel.cpp
    ui/FindPanel/findpanel.h
    ui/ToolsTabWidget/toolstabwidget.cpp
    ui/ToolsTabWidget/toolstabwidget.h

    # Menu bar
    ui/MenuBar/basemenu.h
    ui/MenuBar/builtinmenus.cpp
    ui/MenuBar/builtinmenus.h
    ui/MenuBar/menubarbuilder.cpp
    ui/MenuBar/menubarbuilder.h
    ui/MenuBar/menufactory.cpp
    ui/MenuBar/menufactory.h
    ui/MenuBar/Menus/Build/buildmenu.cpp
    ui/MenuBar/Menus/Build/buildmenu.h
    ui/MenuBar/Menus/Edit/editmenu.cpp
    ui/MenuBar/Menus/Edit/editmenu.h
    ui/MenuBar/Menus/File/filemenu.cpp
    ui/MenuBar/Menus/File/filemenu.h
    ui/MenuBar/Menus/Git/gitmenu.cpp
    ui/MenuBar/Menus/Git/gitmenu.h
    ui/MenuBar/Menus/References/referencesmenu.cpp
    ui/MenuBar/Menus/References/referencesmenu.h
    ui/MenuBar/Menus/Tools/toolsmenu.cpp
    ui/MenuBar/Menus/Tools/toolsmenu.h
    ui/MenuBar/Menus/View/viewmenu.cpp
    ui/MenuBar/Menus/View/viewmenu.h

    # Core services used by the shell
    core/FindEngine/findengine.cpp
    core/FindEngine/findengine.h
    core/FindEngine/findtypes.h
    core/buildman/buildmanager.cpp
    core/buildman/buildmanager.h
    core/icons/iconprovider.cpp
    core/icons/iconprovider.h
    core/locale/LanguageManager.cpp
    core/locale/LanguageManager.h
    core/project/project_info_manager.cpp
    core/project/project_info_manager.h
    core/project/projects_history_manager.cpp
    core/project/projects_history_manager.h
    core/settings/exclusionfilterproxymodel.cpp
    core/settings/exclusionfilterproxymodel.h
    core/update/updatechecker.cpp
    core/update/updatechecker.h
)

target_include_directories(cremniy_shell PUBLIC
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(cremniy_shell
    PUBLIC
        cremniy_config
        cremniy_file_core
        cremniy_settings_core
        cremniy_git_core
        cremniy_module_api
        CodeEditor
        cremniy_terminal_core
        cremniy_module_ascii_chars
        cremniy_module_keyboard_scancodes
        cremniy_module_binary
        cremniy_module_code_editor
        cremniy_module_disassembler
        cremniy_module_stm32_pinout
        cremniy_module_data_converter
        cremniy_module_reverse_calculator
        cremniy_module_shellcode_generator
        Qt6::Core
        Qt6::Widgets
        Qt6::Gui
        Qt6::Concurrent
        Qt6::Svg
        Qt6::Network
    PRIVATE
        cremniy_warnings
)

if(CREMNIY_ENABLE_PCH)
    target_precompile_headers(cremniy_shell PRIVATE
        <QtCore>
        <QtGui>
        <QtWidgets>
    )
endif()

# - - Executable - -
qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    main.cpp
    resources/cremniy_res.qrc
)
target_link_libraries(${PROJECT_NAME} PRIVATE cremniy_shell cremniy_warnings)

# Icon theme: resource files are enumerated at configure time (assets only,
# never sources); CONFIGURE_DEPENDS re-runs the glob when files are added.
file(GLOB_RECURSE PHOICONS_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons/phoicons/*"
)
qt_add_resources(${PROJECT_NAME} "phoicons"
    PREFIX "/icons"
    BASE "resources/icons"
    FILES ${PHOICONS_FILES}
)

# - - Translations - -
set(TS_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/locale/translations/app_ru.ts
    ${CMAKE_CURRENT_SOURCE_DIR}/resources/locale/translations/qtbase_ru.ts
)

qt6_add_translation(QM_FILES ${TS_FILES})

add_custom_target(translations ALL DEPENDS ${QM_FILES})
add_dependencies(${PROJECT_NAME} translations)

if(APPLE)
    set(TRANSLATIONS_DIR "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources/translations")
else()
    set(TRANSLATIONS_DIR "${CMAKE_BINARY_DIR}/Resources/translations")
endif()

file(MAKE_DIRECTORY ${TRANSLATIONS_DIR})

foreach(QM_FILE ${QM_FILES})
    get_filename_component(QM_FILENAME ${QM_FILE} NAME)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${QM_FILE}"
            "${TRANSLATIONS_DIR}/${QM_FILENAME}"
    )
endforeach()

# - - Platform packaging - -
option(CREMNIY_DEPLOY_QT_POST_BUILD
    "Run windeployqt after building so the build tree is runnable (Windows)" ON)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt)

if(WIN32 AND WINDEPLOYQT_EXECUTABLE AND CREMNIY_DEPLOY_QT_POST_BUILD)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${PROJECT_NAME}>
        COMMENT "Deploying Qt dependencies with windeployqt"
    )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
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

# - - Install - -
include(GNUInstallDirs)
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Bundle Qt for self-contained Windows / macOS installs. Linux packages
# (see rpm/cremniy.spec) rely on the distribution's Qt.
if((WIN32 OR APPLE) AND Qt6_VERSION VERSION_GREATER_EQUAL 6.5)
    qt_generate_deploy_app_script(
        TARGET ${PROJECT_NAME}
        OUTPUT_SCRIPT CREMNIY_DEPLOY_SCRIPT
        NO_UNSUPPORTED_PLATFORM_ERROR
    )
    install(SCRIPT ${CREMNIY_DEPLOY_SCRIPT})
endif()

qt_finalize_executable(${PROJECT_NAME})
