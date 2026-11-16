#include "appsettings.h"

#include <QFileInfo>
#include <QSet>
#include <QSettings>
#include <utility>

#include "core/settings/settingsregistry.h"

AppSettings::AppSettings(const SettingsRegistry &registry, QObject *parent)
    : AppSettings(registry, std::make_unique<QSettings>(), parent)
{
}

AppSettings::AppSettings(const SettingsRegistry &registry, std::unique_ptr<QSettings> backend,
                         QObject *parent)
    : QObject(parent)
    , m_registry(registry)
    , m_settings(std::move(backend))
{
}

QString AppSettings::keyLanguage() { return "application/language"; }
QString AppSettings::keyExcludedPatterns() { return "workspace/files/excludedPatterns"; }

QString AppSettings::language() const
{
    const QString stored = m_settings->value(keyLanguage()).toString().trimmed();
    return stored.isEmpty() ? QStringLiteral("en") : stored;
}

void AppSettings::setLanguage(const QString& locale)
{
    m_settings->setValue(keyLanguage(), locale.trimmed());
}

QVariant AppSettings::value(const QString &key, const QVariant &defaultValue) const
{
    return m_settings->value(key, defaultValue);
}

void AppSettings::setValue(const QString &key, const QVariant &value)
{
    m_settings->setValue(key, value);
}

bool AppSettings::contains(const QString &key) const
{
    return m_settings->contains(key);
}

QStringList AppSettings::excludedPatterns() const
{
    const QString raw = m_settings->value(keyExcludedPatterns()).toString();
    if (raw.trimmed().isEmpty())
        return {};
    QStringList list = raw.split(';', Qt::SkipEmptyParts);
    for (QString &p : list)
        p = p.trimmed();
    list.removeAll(QString());
    return list;
}

void AppSettings::setExcludedPatterns(const QStringList &patterns)
{
    m_settings->setValue(keyExcludedPatterns(), patterns.join(';'));
    emit excludedPatternsChanged();
}

bool AppSettings::exportToIni(const QString &filePath, QString *error) const
{
    const QFileInfo fi(filePath);
    if (fi.filePath().trimmed().isEmpty()) {
        if (error) *error = QObject::tr("Empty file path");
        return false;
    }

    QSettings out(fi.filePath(), QSettings::IniFormat);
    out.clear();
    // Экспортируем всё, что знает ядро: настройки приложения и все ключи,
    // которые модули объявили в фабрике настроек. Хардкод-список исчез:
    // новый модуль добавляется в экспорт автоматически через свою схему.
    const QStringList moduleKeys = m_registry.moduleOptionKeys();
    for (const QString& key : {keyLanguage(), keyExcludedPatterns()}) {
        if (m_settings->contains(key))
            out.setValue(key, m_settings->value(key));
    }
    for (const QString& key : moduleKeys) {
        if (m_settings->contains(key))
            out.setValue(key, m_settings->value(key));
    }
    out.sync();
    if (out.status() != QSettings::NoError) {
        if (error) *error = QObject::tr("Failed to write INI file");
        return false;
    }
    return true;
}

bool AppSettings::importFromIni(const QString &filePath, QString *error)
{
    const QFileInfo fi(filePath);
    if (!fi.exists() || !fi.isFile()) {
        if (error) *error = QObject::tr("File does not exist");
        return false;
    }

    QSettings in(fi.filePath(), QSettings::IniFormat);
    if (in.status() != QSettings::NoError) {
        if (error) *error = QObject::tr("Failed to read INI file");
        return false;
    }

    // Импортируем только известные ключи: приложение + схема модулей.
    const QStringList moduleKeys = m_registry.moduleOptionKeys();

    bool excludedChanged = false;
    QSet<QString> changedModuleKeys;

    for (const QString& key : {keyLanguage(), keyExcludedPatterns()}) {
        if (in.contains(key))
            m_settings->setValue(key, in.value(key));
        if (in.contains(key) && key == keyExcludedPatterns())
            excludedChanged = true;
    }
    for (const QString& key : moduleKeys) {
        if (!in.contains(key))
            continue;
        m_settings->setValue(key, in.value(key));
        changedModuleKeys.insert(key);
    }

    m_settings->sync();
    if (m_settings->status() != QSettings::NoError) {
        if (error) *error = QObject::tr("Failed to apply settings");
        return false;
    }

    if (excludedChanged)
        emit excludedPatternsChanged();
    // Ядро не знает, что означают эти ключи; оно лишь сообщает «такой-то
    // ключ изменился», а модуль сам решает, что с этим делать.
    for (const QString& key : std::as_const(changedModuleKeys))
        emit settingsChanged(key);
    return true;
}
