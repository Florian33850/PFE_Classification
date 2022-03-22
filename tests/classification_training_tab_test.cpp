#include <QtTest/QtTest>

#define private public
#define protected public

#include "../src/classification_training_tab.h"

class ClassificationTrainingTabTests: public QObject
{
    Q_OBJECT

    private:

    private Q_SLOTS:
        void testClassificationTrainingTabInstantiation();
        void testChooseTrainingMethodComboBoxInstantiation();
        void testHandleTrainingMethodComboBox();
};

void ClassificationTrainingTabTests::testClassificationTrainingTabInstantiation()
{
    ClassificationTrainingTab *classificationTrainingTab = new ClassificationTrainingTab();
    QVERIFY(classificationTrainingTab != NULL);
}

void ClassificationTrainingTabTests::testChooseTrainingMethodComboBoxInstantiation()
{
    ClassificationTrainingTab *classificationTrainingTab = new ClassificationTrainingTab();
    classificationTrainingTab->addChooseTrainingMethodComboBox();
    QVERIFY(classificationTrainingTab->chooseTrainingMethodComboBox != NULL);
}

void ClassificationTrainingTabTests::testHandleTrainingMethodComboBox()
{
    ClassificationTrainingTab *classificationTrainingTab = new ClassificationTrainingTab();
    
}

// void DataHandlerTests::testReloadPreviewSuccess()
// {
//     if(dataHandler->reloadPreview() != true)
//     {
//         QFAIL("[INFO] Fail to reload");
//     }

// }


QTEST_MAIN(ClassificationTrainingTabTests)
#include "classification_training_tab_test.moc"