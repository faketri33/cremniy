# Developer Guide

The project has a modular architecture without global state; see
[architecture.md](architecture.md).


## Project structure


- `app/` - main windows and the composition root (`AppContext`)
- `core/` - services and base interfaces (settings, git, files, modules)
- `Modules/` - modules: tabs, windows, references
- `ui/`, `widgets/`, `dialogs/` - application shell UI
- `libs/` - editors and the terminal
- `utils/` - helper code



## Tool Tab for working with a file

### Description

A **ToolTab** is a tool tab for the user to work with a file. Examples of **ToolTab**:
- **Code Editor**<br>
<img width="400" height="300" alt="code_tooltab" src="https://github.com/user-attachments/assets/f4d9d9c5-acbb-42ee-a3e1-a2d773c94d89" /><br>
- **HEX Editor**<br>
<img width="400" height="300" alt="hex_tooltab" src="https://github.com/user-attachments/assets/cb66ffa9-1852-4200-809e-77ece6687d32" /><br>
- **Disassembler**<br>
<img width="400" height="300" alt="dasm_tooltab" src="https://github.com/user-attachments/assets/d72c642b-9b02-4dc8-8f03-0224490b4d3e" /><br>

Each **ToolTab** is an independent module registered in the `ModuleManager`.
See [architecture.md](architecture.md) for the overall wiring.

### Operation of tool tabs

- All tabs inherit from `TabBase` (`src/core/modules/TabBase.h`)
- Every module is its own CMake library (`cremniy_module_<name>`) that links
  only `cremniy_module_api`
- A module defines `void register<Name>(ModuleManager&)`; it is called
  explicitly from `registerBuiltinModules()` (`src/app/builtinmodules.cpp`)
- `ToolsTabWidget` asks the application's `ModuleManager` for the registered
  tabs and creates them with the `ModuleContext`

```
TabBase (interface)
    ↓
Module (CodeEditorTab, BinaryTab, ...)   register<Name>(ModuleManager&)
    ↓
registerBuiltinModules()  →  ModuleManager (owned by AppContext)
    ↓
ToolsTabWidget → creator(ModuleContext) → addTab()
```

There is no global state and no static initialisation: registration happens
when `AppContext` is constructed.

### Adding a tab

1. Create `src/Modules/Tabs/<Name>/` with the tab class and a `CMakeLists.txt`
   (`add_library(cremniy_module_<name> STATIC ...)`, link `cremniy_module_api`)
2. Implement the `TabBase` interface
3. Define `register<Name>(ModuleManager&)` in the main `.cpp`:

```cpp
void registerExampleTab(ModuleManager& manager) {
    manager.registerModule<TabBase>(&displayName, "", [](const ModuleContext& ctx) {
        return new ExampleTab(ctx.settings);
    }, 200);
}
```

4. Add `add_subdirectory(<Name>)` to `src/Modules/Tabs/CMakeLists.txt`, link the
   library into `cremniy_shell`, and call the function from
   `registerBuiltinModules()`

### Rules

- Modules **must not depend** on each other or on the application shell
- Include project headers by their path relative to `src/`; do not use `../`
- Dependencies are connected **through CMake** (`target_link_libraries`)
- Modules get services only through their constructor / `ModuleContext`

## Module settings pages

Modules may add a settings page without modifying `SettingsDialog`. Modules that
do not need settings simply do not register one. A page inherits `SettingsPage`
and implements this lifecycle: `load()` reads saved values, `validate()` checks
pending input without saving, and `apply()` persists it after the user accepts.

Define a registration function in the module's source file and call it from
`registerBuiltinSettingsPages()` (`src/app/builtinsettings.cpp`):

```cpp
void registerExampleSettingsPage(SettingsRegistry& registry)
{
    registry.registerModulePage("example", {
        "modules.example",
        "modules",
        []() { return QObject::tr("Modules"); },
        300,
        []() { return QCoreApplication::translate("ExampleModule", "Example"); },
        100,
        {},
        [](AppSettings& settings, QWidget* parent) { return new ExampleSettingsPage(settings, parent); }
    });
}
```

Keep `pageId` and the module owner ID stable and independent of translations.
Do not write settings from widget signals: writing only in `apply()` ensures
that Cancel leaves persisted settings unchanged.
