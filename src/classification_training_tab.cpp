#include "classification_training_tab.h"

ClassificationTrainingTab::ClassificationTrainingTab(Tab *parent)
    : Tab(parent)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(this->mainLayout);

    addChooseTrainingMethodComboBox();

    this->mainLayout->addStretch();
}

void ClassificationTrainingTab::addChooseTrainingMethodComboBox()
{
    chooseTrainingMethodComboBox = new QComboBox();
    chooseTrainingMethodComboBox->addItems(trainingMethodStringList);
    connect(chooseTrainingMethodComboBox, QOverload<int>::of(&QComboBox::activated), this, &ClassificationTrainingTab::handleTrainingMethodComboBox);
    mainLayout->addWidget(chooseTrainingMethodComboBox);
}

void ClassificationTrainingTab::handleTrainingMethodComboBox()
{
    QString newTrainingMethod = chooseTrainingMethodComboBox->currentText();
    ClassificationTrainingWidget *classificationTrainingWidget;
    if(newTrainingMethod.compare("Deep Learning") == 0)
    {
        classificationTrainingWidget = new DeepLearningWidget(this->mainLayout);
    }
    else if(newTrainingMethod.compare("Random Forest") == 0)
    {
        // imageTransformationWidget = createGrayscaleImageTransformation();
    }
    // connect(imageTransformationWidget->getDeleteImageTransformationWidgetButton(), &QPushButton::released, 
    //     [=](){this->handleDeleteImageTransformationWidgetButton(imageTransformationWidget);});
}

