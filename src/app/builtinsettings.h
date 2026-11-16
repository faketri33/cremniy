#ifndef BUILTINSETTINGS_H
#define BUILTINSETTINGS_H

class SettingsRegistry;

/// Registers the settings pages (and the module option schemas they declare).
void registerBuiltinSettingsPages(SettingsRegistry& registry);

#endif // BUILTINSETTINGS_H
