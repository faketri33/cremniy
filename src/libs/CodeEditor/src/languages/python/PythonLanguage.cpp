#include "languages/LanguageRegistry.h"

#include "xml/XmlLanguageHighlighter.h"

#include <QRegularExpression>

void registerPythonLanguage(LanguageRegistry& registry)
{
    registry.registerLanguage({
        QStringLiteral("python"),
        QStringLiteral("Python"),
        {QStringLiteral("py")},
        {},
        QStringLiteral("#"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* {
            return new XmlLanguageHighlighter(
                QStringLiteral(":/languages/python.xml"),
                QRegularExpression(QStringLiteral("#[^\\n]*")),
                QRegularExpression(QStringLiteral("\"[^\"\\n]*\"|'[^'\\n]*'")),
                QRegularExpression(QStringLiteral("\\b(0x[0-9A-Fa-f]+|\\d+(?:\\.\\d+)?)\\b")),
                document);
        }
    });
}
