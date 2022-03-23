#include <QtTest/QtTest>

#include "../src/data_augmentation_tab.h"

class DataAugmentationTabTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testDataAugmentationTabInstantiation();
        void testNewDataHandler();
};

void DataAugmentationTabTests::testDataAugmentationTabInstantiation()
{
    DataAugmentationTab *dataAugmentationTab = new DataAugmentationTab();
    QVERIFY(dataAugmentationTab != NULL);
}

void DataAugmentationTabTests::testNewDataHandler()
{
    DataAugmentationTab *dataAugmentationTab = new DataAugmentationTab();
    
    QWidget *parent1 = NULL;
    std::vector<ImageLabel*> *imagePreviewList1 = new std::vector<ImageLabel*>();
    ImageSelectionHandler *imageSelectionHandler = new ImageSelectionHandler(parent1, imagePreviewList1);

    QWidget *parent2 = NULL;
    std::vector<ImageLabel*> *imagePreviewList2 = new std::vector<ImageLabel*>();
    LymeDatabaseHandler *lymeDatabaseHandler = new LymeDatabaseHandler(parent2, imagePreviewList2);

    dataAugmentationTab->handleNewDataHandler(imageSelectionHandler);
    QVERIFY(dataAugmentationTab->dataHandler == imageSelectionHandler);

    dataAugmentationTab->handleNewDataHandler(lymeDatabaseHandler);
    QVERIFY(dataAugmentationTab->dataHandler == lymeDatabaseHandler);
}

QTEST_MAIN(DataAugmentationTabTests)
#include "data_augmentation_tab_test.moc"
