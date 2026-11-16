#ifndef CODEEDITORSETTINGS_H
#define CODEEDITORSETTINGS_H

#include <QString>

class AppSettings;

// Настройки модуля CodeEditor.
//
// ВСЁ, что касается настроек этого модуля (ключи, умолчания и уведомления
// об изменении), живёт в САМОМ модуле. Ядро (AppSettings) хранит только
// пары "ключ -> значение" и не знает ни одного из этих ключей.
//
// Ключи модуля также объявляются фабрике настроек
// (SettingsRegistry::moduleOptions) в codeeditorsettingspage.cpp — они
// автоматически попадают в экспорт/импорт INI.
namespace CodeEditorSettings {

QString keyGitBlameEnabled();
QString keyGitBlameColor();
QString keyGitBlamePadding();

bool gitBlameEnabled(const AppSettings &settings);
void setGitBlameEnabled(AppSettings &settings, bool enabled);

// Default Gray chain is documented in the settings page UI.
QString gitBlameColor(const AppSettings &settings);
void setGitBlameColor(AppSettings &settings, const QString &color);

int gitBlamePadding(const AppSettings &settings);
void setGitBlamePadding(AppSettings &settings, int padding);

} // namespace CodeEditorSettings

#endif // CODEEDITORSETTINGS_H
