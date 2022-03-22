#include <QtTest/QtTest>

#include "../src/integer_slider.h"

class IntegerSliderTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testIntegerSliderInstantiation();
};

void IntegerSliderTests::testIntegerSliderInstantiation()
{
    IntegerSlider *integerSlider = new IntegerSlider("Integer Slider", 0, 10);
    QVERIFY(integerSlider != NULL);
}

QTEST_MAIN(IntegerSliderTests)
#include "integer_slider_test.moc"
