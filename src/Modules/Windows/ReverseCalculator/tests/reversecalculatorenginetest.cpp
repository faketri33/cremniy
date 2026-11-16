#include <QtTest>

#include "reversecalculatorengine.h"

class ReverseCalculatorEngineTest : public QObject
{
    Q_OBJECT

private slots:
    void parsesNumberBases_data()
    {
        QTest::addColumn<QString>("text");
        QTest::addColumn<qulonglong>("value");
        QTest::addColumn<int>("base");
        QTest::newRow("dec") << "42" << 42ULL << 10;
        QTest::newRow("hex") << "0xFF" << 255ULL << 16;
        QTest::newRow("bin") << "0b101" << 5ULL << 2;
    }
    void parsesNumberBases()
    {
        QFETCH(QString, text);
        QFETCH(qulonglong, value);
        QFETCH(int, base);
        const ParseResult r = ReverseCalculatorEngine().parseExpression(text, 64);
        QVERIFY2(r.ok, qPrintable(r.error));
        QCOMPARE(r.value, value);
        QCOMPARE(r.base, base);
    }

    void respectsPrecedenceAndParens()
    {
        ReverseCalculatorEngine e;
        QCOMPARE(e.parseExpression("2+3*4", 32).value, 14ULL);
        QCOMPARE(e.parseExpression("(2+3)*4", 32).value, 20ULL);
        QCOMPARE(e.parseExpression("1<<4", 32).value, 16ULL);
        QCOMPARE(e.parseExpression("0xF0 & 0x3C", 32).value, 0x30ULL);
    }

    void masksResultToWidth()
    {
        ReverseCalculatorEngine e;
        QCOMPARE(e.parseExpression("0x1FF", 8).value, 0xFFULL);
        QCOMPARE(e.parseExpression("-1", 16).value, 0xFFFFULL);
    }

    void reportsErrors_data()
    {
        QTest::addColumn<QString>("text");
        QTest::newRow("empty") << "";
        QTest::newRow("div0") << "1/0";
        QTest::newRow("mod0") << "1%0";
        QTest::newRow("unmatched-open") << "(1+2";
        QTest::newRow("unmatched-close") << "1+2)";
    }
    void reportsErrors()
    {
        QFETCH(QString, text);
        const ParseResult r = ReverseCalculatorEngine().parseExpression(text, 32);
        QVERIFY(!r.ok);
        QVERIFY(!r.error.isEmpty());
    }

    void formats()
    {
        QCOMPARE(ReverseCalculatorEngine::formatHex(0xAB, 16), QString("0x00AB"));
        QCOMPARE(ReverseCalculatorEngine::formatBin(5, 8), QString("00000101"));
        QCOMPARE(ReverseCalculatorEngine::formatBytes(0x1234, 16), QString("12 34"));
        QCOMPARE(ReverseCalculatorEngine::formatSigned(0xFF, 8), QString("-1"));
        QCOMPARE(ReverseCalculatorEngine::formatUnsigned(0x1FF, 8), QString("255"));
    }

    void swapsEndian()
    {
        QCOMPARE(ReverseCalculatorEngine::swapEndian(0x1234, 16), 0x3412ULL);
        QCOMPARE(ReverseCalculatorEngine::swapEndian(0x12345678, 32), 0x78563412ULL);
    }
};

QTEST_GUILESS_MAIN(ReverseCalculatorEngineTest)
#include "reversecalculatorenginetest.moc"
