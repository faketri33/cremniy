#include "codeeditorsettings.h"

#include "core/settings/appsettings.h"

namespace CodeEditorSettings {

static const QString kDefaultBlameColor = QStringLiteral("#6D6552");
static const int kDefaultBlamePadding = 6;

QString keyGitBlameEnabled() { return QStringLiteral("modules/codeEditor/gitBlameEnabled"); }
QString keyGitBlameColor() { return QStringLiteral("modules/codeEditor/gitBlameColor"); }
QString keyGitBlamePadding() { return QStringLiteral("modules/codeEditor/gitBlamePadding"); }

bool gitBlameEnabled(const AppSettings &settings)
{
    return settings.value(keyGitBlameEnabled(), false).toBool();
}

void setGitBlameEnabled(AppSettings &settings, bool enabled)
{
    if (gitBlameEnabled(settings) == enabled)
        return;

    settings.setValue(keyGitBlameEnabled(), enabled);
    emit settings.settingsChanged(keyGitBlameEnabled());
}

QString gitBlameColor(const AppSettings &settings)
{
    return settings.value(keyGitBlameColor(), kDefaultBlameColor).toString();
}

void setGitBlameColor(AppSettings &settings, const QString &color)
{
    settings.setValue(keyGitBlameColor(), color);
    emit settings.settingsChanged(keyGitBlameColor());
}

int gitBlamePadding(const AppSettings &settings)
{
    return settings.value(keyGitBlamePadding(), kDefaultBlamePadding).toInt();
}

void setGitBlamePadding(AppSettings &settings, int padding)
{
    settings.setValue(keyGitBlamePadding(), padding);
    emit settings.settingsChanged(keyGitBlamePadding());
}

} // namespace CodeEditorSettings
