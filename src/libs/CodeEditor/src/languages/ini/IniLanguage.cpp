#include "languages/LanguageRegistry.h"

#include "core/RuleBasedHighlighter.h"

#include <QRegularExpression>

void registerIniLanguage(LanguageRegistry& registry)
{
    registry.registerLanguage({
        QStringLiteral("ini"),
        QStringLiteral("INI"),
        {QStringLiteral("ini"), QStringLiteral("cfg"), QStringLiteral("conf"), QStringLiteral("properties"),
         QStringLiteral("env")},
        {QStringLiteral(".gitignore"), QStringLiteral(".dockerignore"), QStringLiteral(".env")},
        QStringLiteral(";"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* {
            QVector<RegexRule> rules = {
                {QRegularExpression(QStringLiteral("^\\s*\\[[^\\]]+\\]")), QStringLiteral("Type")},
                {QRegularExpression(QStringLiteral("^\\s*[A-Za-z0-9_.-]+(?=\\s*=)")), QStringLiteral("Function")}
            };

            return new RuleBasedHighlighter(rules, QRegularExpression(QStringLiteral("^[;#][^\\n]*")), document);
        }
    });
}
