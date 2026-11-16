#include "languages/LanguageRegistry.h"

#include "markdown/MarkdownHighlighter.h"

void registerMarkdownLanguage(LanguageRegistry& registry)
{
    registry.registerLanguage({
        QStringLiteral("markdown"),
        QStringLiteral("Markdown"),
        {QStringLiteral("md"), QStringLiteral("markdown")},
        {},
        QString(), // Markdown doesn't have a conventional line comment syntax.
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* { return new MarkdownHighlighter(document); }
    });
}
