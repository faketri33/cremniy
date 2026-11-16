#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "core/git/gitblameservice.h"
#include "core/locale/LanguageManager.h"
#include "core/modules/ModuleManager.h"
#include "ui/MenuBar/menufactory.h"

/**
 * @brief Composition root: creates and owns the application-wide services.
 *
 * Created once in main() after QApplication and destroyed before it, so
 * services are torn down in reverse order of declaration while the Qt event
 * machinery is still alive. Consumers receive the context (or a service)
 * through their constructor; nothing reaches for a global instance.
 */
class AppContext
{
public:
    AppContext();
    AppContext(const AppContext &) = delete;
    AppContext &operator=(const AppContext &) = delete;

    ModuleManager &moduleManager() { return m_moduleManager; }
    MenuFactory &menuFactory() { return m_menuFactory; }
    LanguageManager &languageManager() { return m_languageManager; }
    GitBlameService &gitBlameService() { return m_gitBlameService; }

private:
    LanguageManager m_languageManager;
    ModuleManager m_moduleManager;
    MenuFactory m_menuFactory;
    GitBlameService m_gitBlameService;
};

#endif // APPCONTEXT_H
