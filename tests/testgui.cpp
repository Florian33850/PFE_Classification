#include <QWidget>
#include <QLineEdit>
#include <QtTest/QtTest>

#include "../src/image_label.h"

class TestGui: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testGui();
};

void TestGui::testGui()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}

QTEST_MAIN(TestGui)
#include "testgui.moc"
