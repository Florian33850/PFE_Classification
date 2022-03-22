#include <QtTest/QtTest>

#include "../src/classification_training_tab.h"

class ClassificationTrainingTabTests: public QObject
{
    Q_OBJECT

    private:

    private Q_SLOTS:
        void testClassificationTrainingTabInstantiation();
};

void ClassificationTrainingTabTests::testClassificationTrainingTabInstantiation()
{
    ClassificationTrainingTab *classificationTrainingTab = new ClassificationTrainingTab();
    QVERIFY(classificationTrainingTab != NULL);
}

QTEST_MAIN(ClassificationTrainingTabTests)
#include "classification_training_tab_test.moc"