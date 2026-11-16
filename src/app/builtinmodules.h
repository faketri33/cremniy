#ifndef BUILTINMODULES_H
#define BUILTINMODULES_H

class ModuleManager;

/// Registers every built-in module (tabs, windows, references).
/// Registration order within a group defines the order shown in the menus.
void registerBuiltinModules(ModuleManager& manager);

#endif // BUILTINMODULES_H
