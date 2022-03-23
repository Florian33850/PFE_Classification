#ifndef CLASSIFICATION_TRAINING_TAB_H
#define CLASSIFICATION_TRAINING_TAB_H

#include "tab.h"
#include "classification_training_widget.h"
#include "utils.h"

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

#define ROW_COMBO_BOX 0
#define COLUMN_COMBO_BOX 0
#define ROW_PARAMETERS_LAYOUT 1
#define COLUMN_PARAMETERS_LAYOUT 0
#define ROW_TRAINING_OUTPUT_LAYOUT 2
#define COLUMN_TRAINING_OUTPUT_LAYOUT 0
#define QSTRINGS_ARE_EQUALS 0

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