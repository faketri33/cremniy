#include "widgets/EditorLanguageSupport.h"

#include "languages/LanguageRegistry.h"

namespace EditorLanguageSupport {

QString normalizedFileExt(const LanguageRegistry& registry, const QString& ext)
{
    const QString value = ext.trimmed().toLower();
    const LanguageDefinition& lang = registry.resolveForExtension(value);
    if (&lang == &LanguageRegistry::plainTextLanguage() && lang.id != value)
        return value; // Unknown extension: preserve the raw (lowercased) value, as before.
    return lang.id;
}

QString syntaxKeyForFileName(const LanguageRegistry& registry, const QString& fileName)
{
    return registry.resolveForFile(fileName).id;
}

QString lineCommentPrefix(const LanguageRegistry& registry, const QString& syntaxKey)
{
    if (const LanguageDefinition* lang = registry.find(syntaxKey))
        return lang->lineCommentPrefix;
    return QStringLiteral("//");
}

} // namespace EditorLanguageSupport
