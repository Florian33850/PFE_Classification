#ifndef CLASSIFICATION_TRAINING_WIDGET_H
#define CLASSIFICATION_TRAINING_WIDGET_H

#include "classification_thread.h"
#include "constants.h"

#include <QGroupBox>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QFileDialog>
#include <QLabel>
#include <QScrollArea>
#include <QIntValidator>

class ClassificationTrainingWidget : public QWidget
{
    Q_OBJECT
    public:
        ClassificationTrainingWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout);
    
    protected:
        QVBoxLayout *parametersLayout;
        QVBoxLayout *trainingOutputLayout;

        QGroupBox *formGroupBox;
        QFormLayout *formLayout;
        QPushButton *addClassifierButton;
        QLineEdit *classifierLineEdit;
        QPushButton *addTrainingSetButton;
        QLineEdit *trainingSetLineEdit;
        QLineEdit *heightOfImagesLineEdit;
        QLineEdit *widthOfImagesLineEdit;
        QPushButton *launchTrainingClassifierButton;

        void readAndDisplayOutputTrainingFile();
        void initializeFormParameters();
        void initializeFormLayout();

        void handleWaitingClassification();
        void handleEndingClassification();

        virtual void handleLaunchTrainingClassifierButton() = 0;
};

class DeepLearningWidget : public ClassificationTrainingWidget
{
    Q_OBJECT
    public:
        DeepLearningWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout);
    
    private:
        QPushButton *addTestingSetButton;
        QLineEdit *testingSetLineEdit;
        QLineEdit *numberOfEpochsLineEdit;

        void handleLaunchTrainingClassifierButton();
};

class RandomForestWidget : public ClassificationTrainingWidget
{
    Q_OBJECT
    public:
        RandomForestWidget(QVBoxLayout *parametersLayout, QVBoxLayout *trainingOutputLayout);

    protected:
        QLineEdit *numberOfTreesLineEdit;

        void handleLaunchTrainingClassifierButton();
};

#endif // CLASSIFICATION_TRAINING_WIDGET_H