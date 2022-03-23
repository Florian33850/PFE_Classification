#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab() : Tab()
{
    addChooseTrainingMethodComboBox();
    
    this->parametersLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->parametersLayout, ROW_PARAMETERS_LAYOUT, COLUMN_PARAMETERS_LAYOUT);

    this->trainingOutputLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->trainingOutputLayout, ROW_TRAINING_OUTPUT_LAYOUT, COLUMN_TRAINING_OUTPUT_LAYOUT);

    this->parametersLayout->addStretch();
    this->trainingOutputLayout->addStretch();
}

void ClassificationTrainingTab::addChooseTrainingMethodComboBox()
{
    this->chooseTrainingMethodComboBox = new QComboBox();
    this->chooseTrainingMethodComboBox->addItems(this->trainingMethodStringList);
    connect(this->chooseTrainingMethodComboBox, QOverload<int>::of(&QComboBox::activated), this, &ClassificationTrainingTab::handleTrainingMethodComboBox);
    this->mainLayout->addWidget(this->chooseTrainingMethodComboBox, ROW_COMBO_BOX, COLUMN_COMBO_BOX);
}

void ClassificationTrainingTab::handleTrainingMethodComboBox()
{
    QString newTrainingMethod = this->chooseTrainingMethodComboBox->currentText();

    if(newTrainingMethod.compare("Deep Learning") == QSTRINGS_ARE_EQUALS)
    {
        clearLayout(this->parametersLayout);
        new DeepLearningWidget(this->parametersLayout, this->trainingOutputLayout);
    }
    else if(newTrainingMethod.compare("Random Forest") == QSTRINGS_ARE_EQUALS)
    {
        clearLayout(this->parametersLayout);
        new RandomForestWidget(this->parametersLayout, this->trainingOutputLayout);
    }
}