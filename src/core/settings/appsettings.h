#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <memory>

#include <QObject>
#include <QSettings>
#include <QString>
#include <QStringList>
#include <QVariant>

class SettingsRegistry;

// Центральное хранилище настроек.
//
// Ядро НЕ знает о настройках конкретных модулей. Здесь живут только
// настройки самого приложения (язык, исключённые паттерны) и обобщённый
// доступ «ключ -> значение». Какие ключи существуют, какие у них типы и
// умолчания — объявляет каждый модуль сам через SettingsRegistry
// (см. SettingsPageDescriptor::moduleOptions). Экспорт/импорт INI обходит
// все модульные ключи, зарегистрированные в реестре, поэтому при
// добавлении нового модуля core/settings менять не нужно.
//
// Экземпляр создаётся в composition root (AppContext) и передаётся
// потребителям явно. Он же рассылает уведомления об изменениях.
class AppSettings : public QObject
{
    Q_OBJECT
public:
    /// Uses the default QSettings (organization/application name must be set).
    explicit AppSettings(const SettingsRegistry &registry, QObject *parent = nullptr);
    /// Uses the given backend; lets tests run against a temporary INI file.
    AppSettings(const SettingsRegistry &registry, std::unique_ptr<QSettings> backend,
                QObject *parent = nullptr);

    // ── Настройки самого приложения ───────────────────────────────────────
    QString language() const;
    void setLanguage(const QString& locale);

    // File-tree exclusion patterns ("node_modules", "*.log", ".git").
    QStringList excludedPatterns() const;
    void setExcludedPatterns(const QStringList &patterns);

    // ── Обобщённое хранилище ──────────────────────────────────────────────
    // Модули читают и пишут СВОИ ключи через эти методы. Ключи владеются
    // модулем и объявляются в реестре (SettingsRegistry::moduleOptions),
    // поэтому ядро никогда не должно хардкодить "modules/...".
    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;
    void setValue(const QString &key, const QVariant &value);
    bool contains(const QString &key) const;

    // Import/export settings to share with others (INI file).
    bool exportToIni(const QString &filePath, QString *error = nullptr) const;
    bool importFromIni(const QString &filePath, QString *error = nullptr);

signals:
    void excludedPatternsChanged();
    // Универсальный сигнал: изменился ключ настройки. Ядро рассылает его при
    // импорте INI, а модули — при записи своих ключей. Подписчики сами
    // фильтруют ключи, которые им принадлежат (сравнивая с ключами, которые
    // модуль объявил в своей схеме настроек).
    void settingsChanged(const QString &key);

private:
    static QString keyLanguage();
    static QString keyExcludedPatterns();

    const SettingsRegistry &m_registry;
    std::unique_ptr<QSettings> m_settings;
};

#endif // APPSETTINGS_H
