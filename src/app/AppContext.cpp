#include "app/AppContext.h"

#include "app/builtinmodules.h"
#include "libs/CodeEditor/include/languages/LanguageRegistration.h"
#include "app/builtinsettings.h"
#include "ui/MenuBar/builtinmenus.h"

AppContext::AppContext()
{
    registerAllLanguages(m_languageRegistry);
    registerBuiltinSettingsPages(m_settingsRegistry);
    registerBuiltinModules(m_moduleManager);
    registerBuiltinMenus(m_menuFactory);
}
