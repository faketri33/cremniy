#include "languages/LanguageRegistry.h"

#include "asm/AsmHighlighter.h"

void registerAsmLanguage(LanguageRegistry& registry)
{
    registry.registerLanguage({
        QStringLiteral("asm"),
        QStringLiteral("Assembly"),
        {QStringLiteral("asm"), QStringLiteral("s")},
        {},
        QStringLiteral(";"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* { return new AsmHighlighter(document); }
    });
}
