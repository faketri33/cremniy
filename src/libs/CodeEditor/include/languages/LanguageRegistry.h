#ifndef LANGUAGEREGISTRY_H
#define LANGUAGEREGISTRY_H

#include "languages/LanguageDefinition.h"

#include <QHash>
#include <QString>
#include <QVector>

class QStyleSyntaxHighlighter;
class QTextDocument;

/**
 * @brief Центральный реестр всех поддерживаемых языков редактора кода.
 *
 * Это единственное место, которое CustomCodeEditor опрашивает, чтобы:
 *   - определить язык файла по расширению или имени файла;
 *   - получить префикс комментария для этого языка;
 *   - создать хайлайтер для документа.
 *
 * Реестр — обычный объект без глобального состояния: его создаёт composition
 * root приложения (AppContext) и передаёт редакторам явно.
 * Языки НЕ регистрируются в этом файле или в CustomCodeEditor.cpp. Каждый
 * язык живёт в своей директории src/languages/<name>/ и предоставляет функцию
 * `void register<Name>Language(LanguageRegistry&)`; все они перечислены в
 * registerAllLanguages() (src/languages/core/LanguageRegistration.cpp).
 *
 * Подробное руководство: docs/adding_a_language.md (docs/adding_a_language_ru.md).
 */
class LanguageRegistry {
public:
    LanguageRegistry() = default;

    /// Регистрирует язык. Повторная регистрация одного и того же id
    /// перезаписывает предыдущее определение (полезно для тестов/патчей),
    /// но в обычном коде каждый id должен регистрироваться ровно один раз.
    void registerLanguage(LanguageDefinition definition);

    /// Возвращает определение языка по его id, либо nullptr, если такого
    /// языка нет в реестре.
    const LanguageDefinition* find(const QString& id) const;

    /// Определяет язык по расширению файла (без точки, регистр неважен)
    /// или по точному имени файла. exactFileNames проверяются раньше
    /// расширения. Если совпадений нет — возвращает plainTextLanguage()
    /// (redirect на язык "text", который не подсвечивается).
    const LanguageDefinition& resolveForFile(const QString& fileName) const;

    /// То же самое, но когда на входе уже есть "нормализованное" расширение
    /// (используется для обратной совместимости с существующим кодом,
    /// который оперирует расширениями напрямую).
    const LanguageDefinition& resolveForExtension(const QString& extension) const;

    /// Список всех зарегистрированных языков, отсортированный по displayName.
    /// Полезен для UI (например, меню "Set language...").
    QVector<const LanguageDefinition*> allLanguages() const;

    /// Определение "языка по умолчанию" для неизвестных/бинарных
    /// расширений — обычный текст без подсветки.
    static const LanguageDefinition& plainTextLanguage();

private:
    QHash<QString, LanguageDefinition> m_byId;
    QHash<QString, QString> m_idByExtension;
    QHash<QString, QString> m_idByExactFileName;
};

#endif // LANGUAGEREGISTRY_H
