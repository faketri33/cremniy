#include "languages/LanguageRegistration.h"

class LanguageRegistry;

// One declaration per language; each function is defined next to its
// language in src/languages/<name>/<Name>Language.cpp.
void registerAsmLanguage(LanguageRegistry&);
void registerCSharpLanguage(LanguageRegistry&);
void registerCppLanguage(LanguageRegistry&);
void registerGlslLanguage(LanguageRegistry&);
void registerGoLanguage(LanguageRegistry&);
void registerIniLanguage(LanguageRegistry&);
void registerJavaLanguage(LanguageRegistry&);
void registerJavaScriptLanguage(LanguageRegistry&);
void registerJsonLanguage(LanguageRegistry&);
void registerLuaLanguage(LanguageRegistry&);
void registerMakeLanguage(LanguageRegistry&);
void registerMarkdownLanguage(LanguageRegistry&);
void registerPhpLanguage(LanguageRegistry&);
void registerPythonLanguage(LanguageRegistry&);
void registerRustLanguage(LanguageRegistry&);
void registerShellLanguage(LanguageRegistry&);
void registerSlnLanguage(LanguageRegistry&);
void registerSqlLanguage(LanguageRegistry&);
void registerTomlLanguage(LanguageRegistry&);
void registerXmlLanguage(LanguageRegistry&);
void registerYamlLanguage(LanguageRegistry&);

void registerAllLanguages(LanguageRegistry& registry)
{
    // NOTE for contributors adding a new language: add the declaration above
    // and one call here. Everything else is the new
    // src/languages/<name>/ directory. See docs/adding_a_language.md.
    registerAsmLanguage(registry);
    registerCSharpLanguage(registry);
    registerCppLanguage(registry);
    registerGlslLanguage(registry);
    registerGoLanguage(registry);
    registerIniLanguage(registry);
    registerJavaLanguage(registry);
    registerJavaScriptLanguage(registry);
    registerJsonLanguage(registry);
    registerLuaLanguage(registry);
    registerMakeLanguage(registry);
    registerMarkdownLanguage(registry);
    registerPhpLanguage(registry);
    registerPythonLanguage(registry);
    registerRustLanguage(registry);
    registerShellLanguage(registry);
    registerSlnLanguage(registry);
    registerSqlLanguage(registry);
    registerTomlLanguage(registry);
    registerXmlLanguage(registry);
    registerYamlLanguage(registry);
}
