#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include "core/git/gitblameservice.h"

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
    AppContext() = default;
    AppContext(const AppContext &) = delete;
    AppContext &operator=(const AppContext &) = delete;

    GitBlameService &gitBlameService() { return m_gitBlameService; }

private:
    GitBlameService m_gitBlameService;
};

#endif // APPCONTEXT_H
