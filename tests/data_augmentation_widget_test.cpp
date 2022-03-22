#include <QtTest/QtTest>

#include "../src/data_augmentation_widget.h"

class DataAugmentationWidgetTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testDataAugmentationWidgetInstantiation();
};

void DataAugmentationWidgetTests::testDataAugmentationWidgetInstantiation()
{
    QWidget *parentWidget = new QWidget();
    DataAugmentationWidget *dataAugmentationWidget = new DataAugmentationWidget(parentWidget);
    QVERIFY(dataAugmentationWidget != NULL);
}

QTEST_MAIN(DataAugmentationWidgetTests)
#include "data_augmentation_widget_test.moc"
