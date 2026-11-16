# Архитектура

Cremniy — десктопная IDE на Qt 6 / C++17. Полное описание на английском:
[docs/EN/architecture.md](../../EN/architecture.md). Кратко:

## Нет глобального состояния

Синглтонов нет. `main()` после `QApplication` создаёт один `AppContext`
(`src/app/AppContext.h`) — composition root. Он создаёт и владеет всеми
сервисами (`LanguageRegistry`, `SettingsRegistry`, `AppSettings`,
`ModuleManager`, `MenuFactory`, `LanguageManager`, `GitBlameService`) и
уничтожает их в обратном порядке **до** `QApplication`.

- Зависимости передаются явно через конструкторы; `X::instance()` не используется.
- Оболочка UI получает `AppContext&`, модули — только `ModuleContext`
  (настройки + реестр языков), поэтому библиотеки модулей не зависят от оболочки.
- Регистрация явная и в одном месте: `registerBuiltinModules()`,
  `registerBuiltinMenus()`, `registerBuiltinSettingsPages()`,
  `registerAllLanguages()` — статических инициализаторов нет.
- Фоновые потоки не читают общие объекты: им передаётся копия значений
  (`DisassemblerSettings::Snapshot`).

## Цели сборки

`cremniy` (exe) → `cremniy_shell` (окна, меню, composition root) →
`cremniy_module_*` (по библиотеке на модуль, зависят только от
`cremniy_module_api`) и базовые библиотеки `cremniy_settings_core`,
`cremniy_git_core`, `cremniy_file_core`, `CodeEditor`, `HexEditor`,
`cremniy_terminal_core`. Заголовки подключаются по пути от `src/`.

## Сборка и проверки

`cd src && cmake --preset debug && cmake --build --preset debug && ctest --preset debug`.
Пресеты: `debug`, `release`, `relwithdebinfo`, `asan-ubsan`, `ci-linux`, `fast`,
`clang-tidy`, `clazy`. Опции: `CREMNIY_WARNINGS_AS_ERRORS`, `CREMNIY_SANITIZERS`,
`CREMNIY_ENABLE_PCH`, `CREMNIY_UNITY_BUILD`, `CREMNIY_ENABLE_CLANG_TIDY`.
