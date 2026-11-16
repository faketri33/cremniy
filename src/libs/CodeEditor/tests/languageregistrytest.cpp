#include <QtTest>

#include "languages/LanguageRegistration.h"
#include "languages/LanguageRegistry.h"

class LanguageRegistryTest : public QObject
{
    Q_OBJECT

private slots:
    void emptyRegistryFallsBackToPlainText()
    {
        LanguageRegistry registry;
        QVERIFY(registry.allLanguages().isEmpty());
        QCOMPARE(&registry.resolveForExtension("py"), &LanguageRegistry::plainTextLanguage());
    }

    void registersAllBuiltinLanguages()
    {
        LanguageRegistry registry;
        registerAllLanguages(registry);
        QVERIFY(registry.allLanguages().size() >= 20);
        QCOMPARE(registry.resolveForExtension("py").id, QString("python"));
        QCOMPARE(registry.resolveForFile("main.cpp").id, QString("cpp"));
        QVERIFY(registry.find("python") != nullptr);
        QCOMPARE(&registry.resolveForFile("file.unknownext"), &LanguageRegistry::plainTextLanguage());
    }

    void instancesAreIndependent()
    {
        LanguageRegistry a, b;
        registerAllLanguages(a);
        QVERIFY(b.find("python") == nullptr);
    }
};

QTEST_GUILESS_MAIN(LanguageRegistryTest)
#include "languageregistrytest.moc"
