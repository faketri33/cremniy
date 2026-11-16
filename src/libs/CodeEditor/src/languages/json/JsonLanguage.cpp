#include "languages/LanguageRegistry.h"

#include "QJSONHighlighter.hpp"

void registerJsonLanguage(LanguageRegistry& registry)
{
    registry.registerLanguage({
        QStringLiteral("json"),
        QStringLiteral("JSON"),
        {QStringLiteral("json")},
        {},
        QString(), // JSON has no comment syntax.
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* { return new QJSONHighlighter(document); }
    });
}
