#include <QSettings>
#include <QSignalSpy>
#include <QTemporaryDir>
#include <QtTest>

#include "appsettings.h"
#include "settingsregistry.h"

namespace {
SettingsRegistry makeRegistry()
{
    SettingsRegistry registry;
    SettingsPageDescriptor page;
    page.pageId = "modules.fake";
    page.categoryId = "modules";
    page.categoryTitle = [] { return QStringLiteral("Modules"); };
    page.pageTitle = [] { return QStringLiteral("Fake"); };
    page.createPage = [](AppSettings&, QWidget*) { return nullptr; };
    page.moduleOptions = {{"modules/fake/option", 1}};
    registry.registerModulePage("fake", page);
    return registry;
}
} // namespace

class AppSettingsTest : public QObject
{
    Q_OBJECT

    QTemporaryDir m_dir;

    std::unique_ptr<QSettings> backend(const QString& name) const
    {
        return std::make_unique<QSettings>(m_dir.filePath(name), QSettings::IniFormat);
    }

private slots:
    void initTestCase() { QVERIFY(m_dir.isValid()); }

    void languageDefaultsToEnglish()
    {
        const SettingsRegistry registry = makeRegistry();
        AppSettings s(registry, backend("lang.ini"));
        QCOMPARE(s.language(), QString("en"));
        s.setLanguage(" ru ");
        QCOMPARE(s.language(), QString("ru"));
    }

    void excludedPatternsAreTrimmedAndNotify()
    {
        const SettingsRegistry registry = makeRegistry();
        AppSettings s(registry, backend("excl.ini"));
        QSignalSpy spy(&s, &AppSettings::excludedPatternsChanged);
        s.setExcludedPatterns({"node_modules", "*.log"});
        QCOMPARE(spy.count(), 1);
        QCOMPARE(s.excludedPatterns(), (QStringList{"node_modules", "*.log"}));
    }

    void instancesDoNotShareState()
    {
        const SettingsRegistry registry = makeRegistry();
        AppSettings a(registry, backend("a.ini"));
        AppSettings b(registry, backend("b.ini"));
        a.setValue("k", 5);
        QVERIFY(a.contains("k"));
        QVERIFY(!b.contains("k"));
    }

    void exportImportRoundTripNotifiesModuleKeys()
    {
        const SettingsRegistry registry = makeRegistry();
        AppSettings src(registry, backend("src.ini"));
        src.setLanguage("ru");
        src.setValue("modules/fake/option", 42);
        src.setValue("modules/unknown/option", 7); // not declared => not exported

        const QString file = m_dir.filePath("export.ini");
        QString error;
        QVERIFY2(src.exportToIni(file, &error), qPrintable(error));

        AppSettings dst(registry, backend("dst.ini"));
        QSignalSpy spy(&dst, &AppSettings::settingsChanged);
        QVERIFY2(dst.importFromIni(file, &error), qPrintable(error));

        QCOMPARE(dst.language(), QString("ru"));
        QCOMPARE(dst.value("modules/fake/option").toInt(), 42);
        QVERIFY(!dst.contains("modules/unknown/option"));
        QCOMPARE(spy.count(), 1);
        QCOMPARE(spy.at(0).at(0).toString(), QString("modules/fake/option"));
    }

    void importRejectsMissingFile()
    {
        const SettingsRegistry registry = makeRegistry();
        AppSettings s(registry, backend("miss.ini"));
        QString error;
        QVERIFY(!s.importFromIni(m_dir.filePath("nope.ini"), &error));
        QVERIFY(!error.isEmpty());
    }
};

QTEST_GUILESS_MAIN(AppSettingsTest)
#include "appsettingstest.moc"
