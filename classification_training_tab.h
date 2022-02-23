#ifndef CLASSIFICATION_TRAINING_TAB_H
#define CLASSIFICATION_TRAINING_TAB_H

#include "tab.h"
#include "classification_thread.h"

#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QCheckBox>
#include <QButtonGroup>

class ClassificationTrainingTab : public Tab
{
    Q_OBJECT
    public:
        ClassificationTrainingTab(Tab *parent = nullptr);

    private:
        QVBoxLayout *mainLayout;
        QCheckBox *testAndTrainCheckBox;
        QPushButton *loadTrainingClassifierButton;
        QPushButton *launchTrainingClassifierButton;
        bool isTrainingClassifierLoad;
        bool isTrainingSetLoad;
        bool isTestingSetLoad;
        QString pathToClassifier;
        QString pathToTrainingSet;
        QString pathToTestingSet;

        void addTestAndTrainCheckBox();
        void addLoadTrainingClassifierButton();
        void addLaunchTrainingClassifierButton();

        void handleLoadTrainingClassifierButton();
        void handleLaunchTrainingClassifierButton();
        void handleWaitingClassification();
        void handleEndingClassification();
};
#endif // CLASSIFICATION_TRAINING_TAB_H