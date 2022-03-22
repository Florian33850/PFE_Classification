#include <QtTest/QtTest>

#define protected public

#include "../src/classification_training_tab.h"

class ClassificationTrainingTabTests: public QObject
{
    Q_OBJECT

    private:

    private Q_SLOTS:
        void testClassificationTrainingTabInstantiation();
        void testChooseTrainingMethodComboBoxInstantiation();
        // void testHandleTrainingMethodComboBox();
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

// void ClassificationTrainingTabTests::testHandleTrainingMethodComboBox()
// {
//     ClassificationTrainingTab *classificationTrainingTab = new ClassificationTrainingTab();
//     classificationTrainingTab->chooseTrainingMethodComboBox->setCurrentText("Deep Learning");
// }

QTEST_MAIN(ClassificationTrainingTabTests)
#include "classification_training_tab_test.moc"