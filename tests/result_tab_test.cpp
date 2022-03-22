#include <QtTest/QtTest>

#include "../src/result_tab.h"

class ResultTabTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testImageSelectionHandlerInstantiation();
};

void ResultTabTests::testImageSelectionHandlerInstantiation()
{
    ResultTab *resultTab = new ResultTab();
    QVERIFY(resultTab != NULL);
}

QTEST_MAIN(ResultTabTests)
#include "result_tab_test.moc"
