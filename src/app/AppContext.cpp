#include "app/AppContext.h"

#include "app/builtinmodules.h"
#include "app/builtinsettings.h"
#include "ui/MenuBar/builtinmenus.h"

AppContext::AppContext()
{
    registerBuiltinSettingsPages(m_settingsRegistry);
    registerBuiltinModules(m_moduleManager);
    registerBuiltinMenus(m_menuFactory);
}
