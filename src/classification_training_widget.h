#ifndef CLASSIFICATION_TRAINING_WIDGET_H
#define CLASSIFICATION_TRAINING_WIDGET_H

#include "classification_thread.h"

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
        ClassificationTrainingWidget(QVBoxLayout *mainLayout);
    
    protected:
        QVBoxLayout *mainLayout;
        QGroupBox *formGroupBox;
        QFormLayout *formLayout;

        QPushButton *launchTrainingClassifierButton;

        void readAndDisplayOutputTrainingFile();
        
        void handleAddDirectoryToQlineEdit(QLineEdit *qLineEdit);
        void handleAddFileToQlineEdit(QLineEdit *qLineEdit);
        void handleWaitingClassification();
        void handleEndingClassification();

        virtual void handleLaunchTrainingClassifierButton() = 0;
};
#endif // CLASSIFICATION_TRAINING_WIDGET_H

#ifndef DEEP_LEARNING_WIDGET_H
#define DEEP_LEARNING_WIDGET_H

class DeepLearningWidget : public ClassificationTrainingWidget
{
    public:
        DeepLearningWidget(QVBoxLayout *mainLayout);
    
    private:
        QPushButton *addClassifierButton;
        QLineEdit *classifierLineEdit;
        QPushButton *addTrainingSetButton;
        QLineEdit *trainingSetLineEdit;
        QPushButton *addTestingSetButton;
        QLineEdit *testingSetLineEdit;
        QLineEdit *numberOfEpochsLineEdit;
        QLineEdit *heightOfImagesLineEdit;
        QLineEdit *widthOfImagesLineEdit;

        void handleLaunchTrainingClassifierButton();
};
#endif // DEEP_LEARNING_WIDGET_H

// #ifndef RANDOM_FOREST_WIDGET_H
// #define RANDOM_FOREST_WIDGET_H

// class RandomForestWidget : public ClassificationTrainingWidget
// {
//     public:
//         RandomForestWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, GrayscaleImageTransformation *grayscaleImageTransformation);

//     protected:
//         QPushButton *addClassifierButton;
//         QLineEdit *classifierLineEdit;
//         QPushButton *addTrainingSetButton;
//         QLineEdit *trainingSetLineEdit;
//         QLineEdit *numberOfTreesLineEdit;
//         QLineEdit *heightOfImagesLineEdit;
//         QLineEdit *widthOfImagesLineEdit;
// };
// #endif // RANDOM_FOREST_WIDGET_H