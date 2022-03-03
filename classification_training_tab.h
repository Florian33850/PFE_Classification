#ifndef CLASSIFICATION_TRAINING_TAB_H
#define CLASSIFICATION_TRAINING_TAB_H

#include "tab.h"
#include "classification_thread.h"

#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QCheckBox>
#include <QButtonGroup>
#include <QScrollArea>
#include <QFormLayout>
#include <QLineEdit>
#include <QGroupBox>
#include <QIntValidator>

class ClassificationTrainingTab : public Tab
{
    Q_OBJECT
    public:
        ClassificationTrainingTab(Tab *parent = nullptr);

    private:
        QVBoxLayout *mainLayout;

        QGroupBox *formGroupBox;
        QFormLayout *formLayout;
        QPushButton *addClassifierButton;
        QLineEdit *classifierLineEdit;
        QPushButton *addTrainingSetButton;
        QLineEdit *trainingSetLineEdit;
        QPushButton *addTestingSetButton;
        QLineEdit *testingSetLineEdit;
        QLineEdit *numberOfepochsLineEdit;
        QLineEdit *heightOfImagesLineEdit;
        QLineEdit *widthOfImagesLineEdit;

        QPushButton *loadTrainingClassifierButton;
        QPushButton *launchTrainingClassifierButton;

        void readAndDisplayOutputTrainingFile();

        void addTrainingParametersFormLayout();
        void addLaunchTrainingClassifierButton();

        void handleAddDirectoryToQlineEdit(QLineEdit *qLineEdit);
        void handleAddFileToQlineEdit(QLineEdit *qLineEdit);
        void handleLoadTrainingClassifierButton();
        void handleLaunchTrainingClassifierButton();
        void handleWaitingClassification();
        void handleEndingClassification();
};
#endif // CLASSIFICATION_TRAINING_TAB_H