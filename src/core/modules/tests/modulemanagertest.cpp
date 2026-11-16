#include <QtTest>

#include "core/modules/ModuleManager.h"

// Local stand-ins for the real module base types (intentionally incomplete
// types are supported by ModuleManager, complete ones are used here so the
// creators can return something).
struct FakeTab { int id; };
struct FakeWindow { int id; };
class AppContext {};

class ModuleManagerTest : public QObject
{
    Q_OBJECT

private slots:
    void keepsRegistrationOrderAndPositions()
    {
        ModuleManager m;
        m.registerModule<FakeTab>([] { return QStringLiteral("a"); }, "g",
                                  [](AppContext&) { return new FakeTab{1}; }, 10);
        m.registerModule<FakeTab>([] { return QStringLiteral("b"); }, "g",
                                  [](AppContext&) { return new FakeTab{2}; }, 20);

        const auto& v = m.getByGroup<FakeTab>("g");
        QCOMPARE(v.size(), 2);
        QCOMPARE(v[0].name(), QString("a"));
        QCOMPARE(v[1].position, 20);
    }

    void groupsSortWithEmptyGroupFirst()
    {
        ModuleManager m;
        for (const char* g : {"zeta", "", "alpha"})
            m.registerModule<FakeTab>([] { return QString(); }, g,
                                      [](AppContext&) { return new FakeTab{0}; });
        QCOMPARE(m.getGroups<FakeTab>(), (QList<QString>{"", "alpha", "zeta"}));
    }

    void baseTypesAreIsolated()
    {
        ModuleManager m;
        m.registerModule<FakeTab>([] { return QString(); }, "g",
                                  [](AppContext&) { return new FakeTab{0}; });
        QVERIFY(m.getGroups<FakeWindow>().isEmpty());
        QVERIFY(m.getByGroup<FakeWindow>("g").isEmpty());
    }

    void instancesAreIndependent()
    {
        ModuleManager a, b;
        a.registerModule<FakeTab>([] { return QString(); }, "g",
                                  [](AppContext&) { return new FakeTab{0}; });
        QCOMPARE(a.getGroups<FakeTab>().size(), 1);
        QVERIFY(b.getGroups<FakeTab>().isEmpty());
    }

    void createPassesContextAndChecksBounds()
    {
        ModuleManager m;
        AppContext ctx;
        m.registerModule<FakeTab>([] { return QString(); }, "g",
                                  [](AppContext&) { return new FakeTab{7}; });
        std::unique_ptr<FakeTab> t(m.create<FakeTab>("g", 0, ctx));
        QVERIFY(t);
        QCOMPARE(t->id, 7);
        QVERIFY(!m.create<FakeTab>("g", 1, ctx));
        QVERIFY(!m.create<FakeTab>("missing", 0, ctx));
    }
};

QTEST_GUILESS_MAIN(ModuleManagerTest)
#include "modulemanagertest.moc"
