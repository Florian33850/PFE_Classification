#include <QtTest/QtTest>

#include "../src/preprocessing_tab.h"

class PreprocessingTabTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testPreprocessingTabInstantiation();
        void testPreprocessingTabNewDataHandler();
};

void PreprocessingTabTests::testPreprocessingTabInstantiation()
{
    PreprocessingTab *preprocessingTab = new PreprocessingTab();
    QVERIFY(preprocessingTab != NULL);
}

void PreprocessingTabTests::testPreprocessingTabNewDataHandler()
{
    PreprocessingTab *preprocessingTab = new PreprocessingTab();

    QWidget *parent1 = NULL;
    std::vector<ImageLabel*> *imagePreviewList1 = new std::vector<ImageLabel*>();
    ImageSelectionHandler *dataHandler1 = new ImageSelectionHandler(parent1, imagePreviewList1);

    QWidget *parent2 = NULL;
    std::vector<ImageLabel*> *imagePreviewList2 = new std::vector<ImageLabel*>();
    LymeDatabaseHandler *dataHandler2 = new LymeDatabaseHandler(parent2, imagePreviewList2);

    preprocessingTab->handleNewDataHandler(dataHandler1);
    QVERIFY(preprocessingTab->dataHandler == dataHandler1);
    preprocessingTab->handleNewDataHandler(dataHandler2);
    QVERIFY(preprocessingTab->dataHandler == dataHandler2);
}

QTEST_MAIN(PreprocessingTabTests)
#include "preprocessing_tab_test.moc"
