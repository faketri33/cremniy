#include "languages/LanguageRegistry.h"
#include "languages/LanguageRuleHelpers.h"

#include <QRegularExpression>

void registerGoLanguage(LanguageRegistry& registry)
{
    using namespace LanguageRuleHelpers;

    registry.registerLanguage({
        QStringLiteral("go"),
        QStringLiteral("Go"),
        {QStringLiteral("go")},
        {},
        QStringLiteral("//"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* {
            QVector<RegexRule> rules = keywordsAndTypesRules({
                QStringLiteral("break"), QStringLiteral("case"), QStringLiteral("chan"), QStringLiteral("const"),
                QStringLiteral("continue"), QStringLiteral("default"), QStringLiteral("defer"), QStringLiteral("else"),
                QStringLiteral("fallthrough"), QStringLiteral("for"), QStringLiteral("func"), QStringLiteral("go"),
                QStringLiteral("goto"), QStringLiteral("if"), QStringLiteral("import"), QStringLiteral("interface"),
                QStringLiteral("map"), QStringLiteral("package"), QStringLiteral("range"), QStringLiteral("return"),
                QStringLiteral("select"), QStringLiteral("struct"), QStringLiteral("switch"), QStringLiteral("type"),
                QStringLiteral("var")
            }, {
                QStringLiteral("int"), QStringLiteral("int8"), QStringLiteral("int16"), QStringLiteral("int32"),
                QStringLiteral("int64"), QStringLiteral("uint"), QStringLiteral("float32"), QStringLiteral("float64"),
                QStringLiteral("bool"), QStringLiteral("byte"), QStringLiteral("rune"), QStringLiteral("string")
            });

            return new RuleBasedHighlighter(rules, QRegularExpression(QStringLiteral("//[^\\n]*")), document);
        }
    });
}
