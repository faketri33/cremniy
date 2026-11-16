#include <QApplication>
#include <QSettings>
#include <QTemporaryDir>
#include <QtTest>

#include "app/AppContext.h"
#include "core/modules/ReferenceBase.h"
#include "core/modules/TabBase.h"
#include "core/modules/WindowBase.h"

// Integration test of the composition root: every built-in module, menu and
// settings page that the application registers must be present and creatable.
class AppContextTest : public QObject
{
    Q_OBJECT

    QTemporaryDir m_settingsDir;

private slots:
    void initTestCase()
    {
        QVERIFY(m_settingsDir.isValid());
        QCoreApplication::setOrganizationName("CremniyTest");
        QCoreApplication::setApplicationName("AppContextTest");
        QSettings::setDefaultFormat(QSettings::IniFormat);
        QSettings::setPath(QSettings::IniFormat, QSettings::UserScope, m_settingsDir.path());
    }

    void registersBuiltinTabs()
    {
        AppContext ctx;
        const auto& manager = ctx.moduleManager();
        QCOMPARE(manager.getGroups<TabBase>(), (QList<QString>{"", "always"}));
        QCOMPARE(manager.getByGroup<TabBase>("always").size(), 2);
        QCOMPARE(manager.getByGroup<TabBase>("").size(), 2);
        QCOMPARE(manager.getByGroup<WindowBase>("").size(), 3);
        QCOMPARE(manager.getByGroup<ReferenceBase>("").size(), 2);
    }

    void everyModuleCanBeCreated()
    {
        AppContext ctx;
        const auto& manager = ctx.moduleManager();
        int created = 0;
        for (const QString& group : manager.getGroups<TabBase>())
            for (const auto& desc : manager.getByGroup<TabBase>(group)) {
                std::unique_ptr<TabBase> tab(desc.creator(ctx.moduleContext()));
                QVERIFY2(tab, qPrintable(desc.name()));
                ++created;
            }
        for (const auto& desc : manager.getByGroup<WindowBase>("")) {
            std::unique_ptr<WindowBase> w(desc.creator(ctx.moduleContext()));
            QVERIFY2(w, qPrintable(desc.name()));
            ++created;
        }
        for (const auto& desc : manager.getByGroup<ReferenceBase>("")) {
            std::unique_ptr<ReferenceBase> r(desc.creator(ctx.moduleContext()));
            QVERIFY2(r, qPrintable(desc.name()));
            ++created;
        }
        QCOMPARE(created, 9); // 4 tabs + 3 windows + 2 references
    }

    void menusKeepTheirOrderAndAreCreatable()
    {
        AppContext ctx;
        const QStringList ids = ctx.menuFactory().availableMenus();
        QCOMPARE(ids, (QStringList{"1", "2", "3", "4", "5", "6", "7"}));
        for (const QString& id : ids) {
            std::unique_ptr<BaseMenu> menu(ctx.menuFactory().create(id, ctx));
            QVERIFY2(menu, qPrintable(id));
            QVERIFY(!menu->title().isEmpty());
        }
    }

    void registersSettingsPagesAndSchemas()
    {
        AppContext ctx;
        QCOMPARE(ctx.settingsRegistry().pages().size(), 4);
        const QStringList keys = ctx.settingsRegistry().moduleOptionKeys();
        QVERIFY(keys.contains("modules/codeEditor/gitBlameEnabled"));
        QVERIFY(keys.contains("modules/disassembler/backend"));
    }

    void registersLanguages()
    {
        AppContext ctx;
        QVERIFY(ctx.languageRegistry().find("python") != nullptr);
        QVERIFY(ctx.languageRegistry().allLanguages().size() >= 20);
    }

    void contextsAreIndependent()
    {
        AppContext a;
        AppContext b;
        QVERIFY(&a.moduleManager() != &b.moduleManager());
        QVERIFY(&a.languageRegistry() != &b.languageRegistry());
    }
};

QTEST_MAIN(AppContextTest)
#include "appcontexttest.moc"
