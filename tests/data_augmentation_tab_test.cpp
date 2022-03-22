#include <QtTest/QtTest>

#include "../src/data_augmentation_tab.h"

class DataAugmentationTabTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testDataAugmentationTabInstantiation();
};

void DataAugmentationTabTests::testDataAugmentationTabInstantiation()
{
    DataAugmentationTab *dataAugmentationTab = new DataAugmentationTab();
    QVERIFY(dataAugmentationTab != NULL);
}

QTEST_MAIN(DataAugmentationTabTests)
#include "data_augmentation_tab_test.moc"
