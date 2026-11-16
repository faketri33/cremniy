#include "app/AppContext.h"

#include "app/builtinmodules.h"
#include "ui/MenuBar/builtinmenus.h"

AppContext::AppContext()
{
    registerBuiltinModules(m_moduleManager);
    registerBuiltinMenus(m_menuFactory);
}
