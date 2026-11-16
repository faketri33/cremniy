# Architecture

Cremniy is a Qt 6 / C++17 desktop IDE. This page describes how the code is
wired together and how the build is organised.

## No global state: the composition root

There are no singletons. `main()` creates one `AppContext`
(`src/app/AppContext.h`) right after `QApplication`; it creates and owns every
application-wide service, in dependency order, and destroys them in reverse
order **before** `QApplication` goes away:

| Service | Purpose |
|---|---|
| `LanguageRegistry` | syntax-highlighting languages of the code editor |
| `SettingsRegistry` | settings pages and the option schema of every module |
| `AppSettings` | persistent settings (owns the `QSettings`), emits change signals |
| `ModuleManager` | registry of tabs, windows and reference modules |
| `ModuleContext` | the narrow view of the above that modules may use |
| `MenuFactory` | menu-bar menus |
| `LanguageManager` | UI translators |
| `GitBlameService` | asynchronous git blame |

Rules:

- Dependencies are passed explicitly, through constructors. Nothing calls
  `X::instance()`. Owners are explicit: `std::unique_ptr`, a value member, or
  a `QObject` parent - never both for the same object.
- UI shell classes receive `AppContext&`; modules receive only the
  `ModuleContext` (settings + language registry) when they are created, so
  module libraries do not depend on the shell.
- Registration is explicit, in one place each - no static initialisers:
  `registerBuiltinModules()` (`app/builtinmodules.cpp`),
  `registerBuiltinMenus()` (`ui/MenuBar/builtinmenus.cpp`),
  `registerBuiltinSettingsPages()` (`app/builtinsettings.cpp`),
  `registerAllLanguages()` (`libs/CodeEditor/.../LanguageRegistration.cpp`).
- A background worker never reads shared objects: pass it a value snapshot
  (see `DisassemblerSettings::Snapshot`).

## Targets

```
cremniy (executable: main.cpp + resources)
 └─ cremniy_shell            windows, panels, menus, composition root
     ├─ cremniy_module_*     one static library per module (tabs, windows, references)
     │    └─ cremniy_module_api   TabBase / WindowBase / ReferenceBase / ModuleManager / ModuleContext
     ├─ cremniy_settings_core    AppSettings, SettingsRegistry
     ├─ cremniy_git_core         libgit2 wrapper, GitBlameService
     ├─ cremniy_file_core        FileDataBuffer, FileContext, FileManager
     ├─ CodeEditor, HexEditor, cremniy_terminal_core   widgets (depend only on cremniy_file_core)
     └─ cremniy_utils, cremniy_config
```

Modules never depend on `cremniy_shell` or on each other. Headers are included
by their path relative to `src/` (`#include "core/file/FileDataBuffer.h"`).

## Build

- One top-level `src/CMakeLists.txt`; helper modules in `src/cmake/`
  (`Warnings`, `Sanitizers`, `Tooling`, `Libgit2`).
- First-party targets link the `cremniy_warnings` interface target
  (`-Wall -Wextra -Wpedantic`, `/W4`). The tree is warning-free with GCC;
  `-DCREMNIY_WARNINGS_AS_ERRORS=ON` makes warnings fatal.
- No `file(GLOB)` over sources. (Icon assets are globbed with
  `CONFIGURE_DEPENDS`.)
- Presets (`src/CMakePresets.json`): `debug`, `release`, `relwithdebinfo`,
  `asan-ubsan`, `ci-linux`, `fast` (PCH + unity), `clang-tidy`, `clazy`.
- Speed options (off by default): `CREMNIY_ENABLE_PCH`,
  `CREMNIY_UNITY_BUILD` (shell only), `CREMNIY_ENABLE_CLANG_TIDY`.
- Tests are Qt Test + CTest; `ctest --preset debug`.

## Adding things

**A module** (tab, window, reference)

1. Create `src/Modules/<Kind>/<Name>/` with its class and a `CMakeLists.txt`
   defining `add_library(cremniy_module_<name> STATIC ...)` that links
   `cremniy_module_api` (`PUBLIC`).
2. In the module's main `.cpp` define
   `void register<Name>(ModuleManager& manager)` that calls
   `manager.registerModule<TabBase>(&displayName, group, [](const ModuleContext& ctx) { return new MyTab(ctx.settings); }, position);`
3. Add `add_subdirectory(<Name>)` to the group's `CMakeLists.txt`, link the
   library in `cremniy_shell` (root `CMakeLists.txt`), and add the
   declaration + call in `app/builtinmodules.cpp`.

**A settings page**: define `void register<Name>SettingsPage(SettingsRegistry&)`
next to the page (it calls `registry.registerModulePage(...)`; `createPage`
receives `AppSettings&`), then list it in `app/builtinsettings.cpp`. Module
settings are free functions taking `AppSettings&`
(see `Modules/Tabs/CodeEditor/codeeditorsettings.h`).

**A language**: see [adding_a_language.md](adding_a_language.md).

**A menu**: add the class under `ui/MenuBar/Menus/` and register it with a new
id in `ui/MenuBar/builtinmenus.cpp` (ids define the order).

## Tests

| Test | Covers |
|---|---|
| `appcontexttest` | composition root: all modules/menus/pages register and can be created |
| `modulemanagertest`, `languageregistrytest`, `appsettingstest` | services, runnable now that they are not singletons |
| `reversecalculatorenginetest` | pure logic of the reverse calculator |
| `gitcoretest`, `terminal_pty` | git core, pty |
