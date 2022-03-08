#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab(Tab *parent)
    : Tab(parent)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(this->mainLayout);

    this->parametersLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->parametersLayout);

    this->trainingOutputLayout = new QVBoxLayout;
    this->mainLayout->addLayout(this->trainingOutputLayout);

    addChooseTrainingMethodComboBox();

    this->mainLayout->addStretch();
    this->parametersLayout->addStretch();
    this->trainingOutputLayout->addStretch();
}

void ClassificationTrainingTab::addChooseTrainingMethodComboBox()
{
    chooseTrainingMethodComboBox = new QComboBox();
    chooseTrainingMethodComboBox->addItems(trainingMethodStringList);
    connect(chooseTrainingMethodComboBox, QOverload<int>::of(&QComboBox::activated), this, &ClassificationTrainingTab::handleTrainingMethodComboBox);
    mainLayout->insertWidget(0, chooseTrainingMethodComboBox);
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