#include <QtTest/QtTest>

#include "../src/result_tab.h"

class ResultTabTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testResultTabInstantiation();
};

void ResultTabTests::testResultTabInstantiation()
{
    ResultTab *resultTab = new ResultTab();
    QVERIFY(resultTab != NULL);
}

QTEST_MAIN(ResultTabTests)
#include "result_tab_test.moc"
