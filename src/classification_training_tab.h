#ifndef CLASSIFICATION_TRAINING_TAB_H
#define CLASSIFICATION_TRAINING_TAB_H

#include "tab.h"
#include "classification_training_widget.h"

#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QButtonGroup>
#include <QScrollArea>
#include <QFormLayout>
#include <QGroupBox>
#include <QIntValidator>
#include <QComboBox>
#include <QFileDialog>
#include <QLineEdit>

class ClassificationTrainingTab : public Tab
{
    Q_OBJECT
    public:
        ClassificationTrainingTab();

    protected:
        QVBoxLayout *parametersLayout;
        QVBoxLayout *trainingOutputLayout;

        QComboBox *chooseTrainingMethodComboBox;
        QStringList trainingMethodStringList = {"Deep Learning", "Random Forest"};

        void addChooseTrainingMethodComboBox();

        void handleTrainingMethodComboBox();
};
#endif // CLASSIFICATION_TRAINING_TAB_H