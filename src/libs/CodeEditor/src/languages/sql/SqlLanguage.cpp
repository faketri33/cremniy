#include "languages/LanguageRegistry.h"
#include "languages/LanguageRuleHelpers.h"

#include <QRegularExpression>

void registerSqlLanguage(LanguageRegistry& registry)
{
    using namespace LanguageRuleHelpers;

    registry.registerLanguage({
        QStringLiteral("sql"),
        QStringLiteral("SQL"),
        {QStringLiteral("sql")},
        {},
        QStringLiteral("--"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* {
            QVector<RegexRule> rules = wordRules({
                QStringLiteral("select"), QStringLiteral("from"), QStringLiteral("where"), QStringLiteral("insert"),
                QStringLiteral("into"), QStringLiteral("update"), QStringLiteral("delete"), QStringLiteral("join"),
                QStringLiteral("left"), QStringLiteral("right"), QStringLiteral("inner"), QStringLiteral("outer"),
                QStringLiteral("group"), QStringLiteral("by"), QStringLiteral("order"), QStringLiteral("limit"),
                QStringLiteral("create"), QStringLiteral("table"), QStringLiteral("alter"), QStringLiteral("drop"),
                QStringLiteral("index"), QStringLiteral("values"), QStringLiteral("set"), QStringLiteral("and"),
                QStringLiteral("or"), QStringLiteral("not"), QStringLiteral("null")
            }, QStringLiteral("Keyword"));

            return new RuleBasedHighlighter(rules, QRegularExpression(QStringLiteral("--[^\\n]*")), document);
        }
    });
}
