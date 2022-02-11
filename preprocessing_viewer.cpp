#include "preprocessing_viewer.h"

PreprocessingViewer::PreprocessingViewer(ImageCollection *imageCollection, QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    mainLayout->setSpacing(1);
    mainLayout->setMargin(1);

    this->imageCollection = imageCollection;

    launchPreprocessingButton = new QPushButton("Launch preprocessing");
    connect(launchPreprocessingButton, &QPushButton::released, this, &PreprocessingViewer::handleLaunchPreprocessingButton);
    mainLayout->addWidget(launchPreprocessingButton);

    QStringList preprocessingList = {"Add Preprocessing", "Mirrored", "Blur", "Greyscale"};
    addPreprocessingComboBox = new QComboBox();
    addPreprocessingComboBox->addItems(preprocessingList);
    connect(addPreprocessingComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PreprocessingViewer::handleAddPreprocessingComboBox);
    mainLayout->addWidget(addPreprocessingComboBox);
}

void PreprocessingViewer::handleLaunchPreprocessingButton()
{
    for(Preprocessing *preprocessing : qWidgetList)
    {
        preprocessing->runPreprocess(imageCollection);
    }
}

void PreprocessingViewer::handleAddPreprocessingComboBox()
{
    QString newPreprocessing = addPreprocessingComboBox->currentText();
    if(newPreprocessing.compare("Mirrored") == 0)
    {
        handleMirrored();
    }
}

void PreprocessingViewer::handleMirrored()
{
    qWidgetList.push_back(new Mirrored());
    QLabel *label = new QLabel(this);
    label->setText("Mirrored");
    mainLayout->addWidget(label);
}