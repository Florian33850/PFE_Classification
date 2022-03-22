#include <QtTest/QtTest>

#include "../src/classification_training_widget.h"

class ClassificationTrainingWidgetTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testDeepLearningWidgetInstantiation();
        void testRandomForestWidgetInstantiation();
};

void ClassificationTrainingWidgetTests::testDeepLearningWidgetInstantiation()
{
    QVBoxLayout *parametersLayout = new QVBoxLayout();
    QVBoxLayout *trainingOutputLayout = new QVBoxLayout();
    DeepLearningWidget *deepLearningWidget = new DeepLearningWidget(parametersLayout, trainingOutputLayout);
    QVERIFY(deepLearningWidget != NULL);
}

void ClassificationTrainingWidgetTests::testRandomForestWidgetInstantiation()
{
    QVBoxLayout *parametersLayout = new QVBoxLayout();
    QVBoxLayout *trainingOutputLayout = new QVBoxLayout();
    RandomForestWidget *randomForestWidget = new RandomForestWidget(parametersLayout, trainingOutputLayout);
    QVERIFY(randomForestWidget != NULL);
}

QTEST_MAIN(ClassificationTrainingWidgetTests)
#include "classification_training_widget_test.moc"
