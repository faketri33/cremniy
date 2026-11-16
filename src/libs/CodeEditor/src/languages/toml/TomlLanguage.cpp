#include "languages/LanguageRegistry.h"
#include "languages/LanguageRuleHelpers.h"

#include <QRegularExpression>

void registerTomlLanguage(LanguageRegistry& registry)
{
    using namespace LanguageRuleHelpers;

    registry.registerLanguage({
        QStringLiteral("toml"),
        QStringLiteral("TOML"),
        {QStringLiteral("toml")},
        {},
        QStringLiteral("#"),
        [](QTextDocument* document) -> QStyleSyntaxHighlighter* {
            QVector<RegexRule> rules = wordRules({QStringLiteral("true"), QStringLiteral("false")}, QStringLiteral("Keyword"));
            rules.append({QRegularExpression(QStringLiteral("^\\s*\\[[^\\]]+\\]")), QStringLiteral("Type")});
            rules.append({QRegularExpression(QStringLiteral("^\\s*[A-Za-z0-9_.-]+(?=\\s*=)")), QStringLiteral("Function")});

            return new RuleBasedHighlighter(rules, QRegularExpression(QStringLiteral("#[^\\n]*")), document);
        }
    });
}
