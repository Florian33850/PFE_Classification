#include <QWidget>
#include <QLineEdit>
#include <QtTest/QtTest>

#include "../src/image_label.h"

class TestGui: public QObject
{
    Q_OBJECT

private Q_SLOTS:
  void testELODIE();
  void testGui();

};

void TestGui::testELODIE()
{
  QLineEdit lineEdit;
  
  QTest::keyClicks(&lineEdit, "hello world");
  
  QCOMPARE(lineEdit.text(), QString("hello world"));
}


void TestGui::testGui()
{
    QLineEdit lineEdit;

    QTest::keyClicks(&lineEdit, "hello world");

    QCOMPARE(lineEdit.text(), QString("hello world"));
}

QTEST_MAIN(TestGui)
#include "testgui.moc"
