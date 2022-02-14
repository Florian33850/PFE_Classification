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

    QStringList preprocessingList = {"Add Preprocessing", "Mirrored", "Blur", "Grayscale"};
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
    else if(newPreprocessing.compare("Grayscale") == 0)
    {
        handleGrayscale();
    }
}

void PreprocessingViewer::handleMirrored()
{
    Mirrored *newMirrorPreprocess = new Mirrored();
    qWidgetList.push_back(newMirrorPreprocess);
    newMirrorPreprocess->displayUI(mainLayout, this);
}

void PreprocessingViewer::handleGrayscale()
{
    Grayscale *newGrayscalePreprocess = new Grayscale();
    qWidgetList.push_back(newGrayscalePreprocess);
    newGrayscalePreprocess->displayUI(mainLayout, this);
}

