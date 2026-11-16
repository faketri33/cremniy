#include "languages/LanguageRegistry.h"

#include "QCXXHighlighter.hpp"

void registerCppLanguage(LanguageRegistry& registry)
{
    registry.registerLanguage({
        QStringLiteral("cpp"),
        QStringLiteral("C++"),
        {QStringLiteral("cpp"), QStringLiteral("hpp"), QStringLiteral("cc"), QStringLiteral("cxx"),
         QStringLiteral("hh"), QStringLiteral("hxx")},
        {},
        QStringLiteral("//"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* { return new QCXXHighlighter(document); }
    });

    registry.registerLanguage({
        QStringLiteral("c"),
        QStringLiteral("C"),
        {QStringLiteral("c"), QStringLiteral("h")},
        {},
        QStringLiteral("//"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* { return new QCXXHighlighter(document); }
    });
}
