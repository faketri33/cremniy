#include "app/AppContext.h"

#include "ui/MenuBar/builtinmenus.h"

AppContext::AppContext()
{
    registerBuiltinMenus(m_menuFactory);
}
