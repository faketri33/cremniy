#include "languages/LanguageRegistry.h"
#include "languages/LanguageRuleHelpers.h"

#include <QRegularExpression>

void registerSlnLanguage(LanguageRegistry& registry)
{
    using namespace LanguageRuleHelpers;

    registry.registerLanguage({
        QStringLiteral("sln"),
        QStringLiteral("Visual Studio Solution"),
        {QStringLiteral("sln")},
        {},
        QStringLiteral("#"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* {
            QVector<RegexRule> rules = wordRules({
                QStringLiteral("Project"), QStringLiteral("EndProject"), QStringLiteral("Global"),
                QStringLiteral("EndGlobal"), QStringLiteral("GlobalSection"), QStringLiteral("EndGlobalSection")
            }, QStringLiteral("Keyword"));
            rules.append({QRegularExpression(QStringLiteral("\"[^\"]+\"")), QStringLiteral("String")});

            return new RuleBasedHighlighter(rules, QRegularExpression(QStringLiteral("^#.*$")), document);
        }
    });
}
