#include "builtinmenus.h"

#include "ui/MenuBar/menufactory.h"
#include "ui/MenuBar/Menus/File/filemenu.h"
#include "ui/MenuBar/Menus/Edit/editmenu.h"
#include "ui/MenuBar/Menus/View/viewmenu.h"
#include "ui/MenuBar/Menus/Build/buildmenu.h"
#include "ui/MenuBar/Menus/Tools/toolsmenu.h"
#include "ui/MenuBar/Menus/References/referencesmenu.h"
#include "ui/MenuBar/Menus/Git/gitmenu.h"

void registerBuiltinMenus(MenuFactory& factory)
{
    factory.registerMenu("1", [](AppContext&) { return new FileMenu(); });
    factory.registerMenu("2", [](AppContext&) { return new EditMenu(); });
    factory.registerMenu("3", [](AppContext&) { return new ViewMenu(); });
    factory.registerMenu("4", [](AppContext&) { return new BuildMenu(); });
    factory.registerMenu("5", [](AppContext&) { return new ToolsMenu(); });
    factory.registerMenu("6", [](AppContext&) { return new ReferencesMenu(); });
    factory.registerMenu("7", [](AppContext&) { return new GitMenu(); });
}
