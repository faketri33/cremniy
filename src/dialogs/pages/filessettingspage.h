#ifndef FILESSETTINGSPAGE_H
#define FILESSETTINGSPAGE_H

#include "core/settings/settingspage.h"

class QPlainTextEdit;

class AppSettings;

class FilesSettingsPage : public SettingsPage
{
    Q_OBJECT

public:
    explicit FilesSettingsPage(AppSettings& settings, QWidget* parent = nullptr);

    void load() override;
    bool validate(QString* errorMessage) const override;
    void apply() override;

private:
    AppSettings& m_settings;
    QPlainTextEdit* m_excludedPatterns = nullptr;
};

#endif // FILESSETTINGSPAGE_H
