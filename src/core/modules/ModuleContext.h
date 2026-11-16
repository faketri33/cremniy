#ifndef MODULECONTEXT_H
#define MODULECONTEXT_H

class AppSettings;
class LanguageRegistry;

/// The services a module may use when it is created. A deliberately narrow
/// view of the application context, so module libraries do not depend on the
/// application shell. Only references: owned by AppContext.
struct ModuleContext {
    AppSettings &settings;
    const LanguageRegistry &languages;
};

#endif // MODULECONTEXT_H
