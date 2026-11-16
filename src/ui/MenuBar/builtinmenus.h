#ifndef BUILTINMENUS_H
#define BUILTINMENUS_H

class MenuFactory;

/// Registers all built-in menus. The id defines the order in the menu bar.
void registerBuiltinMenus(MenuFactory& factory);

#endif // BUILTINMENUS_H
