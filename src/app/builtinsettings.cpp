#include "builtinsettings.h"

class SettingsRegistry;

// Each page defines its registration function next to its implementation.
void registerGeneralSettingsPage(SettingsRegistry&);
void registerFilesSettingsPage(SettingsRegistry&);
void registerCodeEditorSettingsPage(SettingsRegistry&);
void registerDisassemblerSettingsPage(SettingsRegistry&);

void registerBuiltinSettingsPages(SettingsRegistry& registry)
{
    registerGeneralSettingsPage(registry);
    registerFilesSettingsPage(registry);
    registerCodeEditorSettingsPage(registry);
    registerDisassemblerSettingsPage(registry);
}
