#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab()
{
    this->mainLayout = new QGridLayout;
    this->setLayout(this->mainLayout);

    this->parametersLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->parametersLayout, 1, 0);

    this->trainingOutputLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->trainingOutputLayout, 2, 0);

    addChooseTrainingMethodComboBox();

    this->parametersLayout->addStretch();
    this->trainingOutputLayout->addStretch();
}

void ClassificationTrainingTab::addChooseTrainingMethodComboBox()
{
    this->chooseTrainingMethodComboBox = new QComboBox();
    this->chooseTrainingMethodComboBox->addItems(this->trainingMethodStringList);
    connect(this->chooseTrainingMethodComboBox, QOverload<int>::of(&QComboBox::activated), this, &ClassificationTrainingTab::handleTrainingMethodComboBox);
    mainLayout->addWidget(this->chooseTrainingMethodComboBox, 0, 0);
}

void ClassificationTrainingTab::handleTrainingMethodComboBox()
{
    QString newTrainingMethod = chooseTrainingMethodComboBox->currentText();
    ClassificationTrainingWidget *classificationTrainingWidget;
    if(newTrainingMethod.compare("Deep Learning") == 0)
    {
        clearLayout(this->parametersLayout);
        classificationTrainingWidget = new DeepLearningWidget(this->parametersLayout, this->trainingOutputLayout);
    }
    else if(newTrainingMethod.compare("Random Forest") == 0)
    {
        clearLayout(this->parametersLayout);
        classificationTrainingWidget = new RandomForestWidget(this->parametersLayout, this->trainingOutputLayout);
    }
}