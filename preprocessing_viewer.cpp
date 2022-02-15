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
    connect(addPreprocessingComboBox, QOverload<int>::of(&QComboBox::activated), this, &PreprocessingViewer::handleAddPreprocessingComboBox);
    mainLayout->addWidget(addPreprocessingComboBox);

    mainLayout->addStretch();
}

void PreprocessingViewer::handleLaunchPreprocessingButton()
{
    for(Preprocessing *preprocessing : preprocessingList)
    {
        preprocessing->runPreprocess(imageCollection);
    }
}

void PreprocessingViewer::handleAddPreprocessingComboBox()
{
    QString newPreprocessing = addPreprocessingComboBox->currentText();
    PreprocessingWidget *preprocessingWidget;
    if(newPreprocessing.compare("Mirrored") == 0)
    {
        preprocessingWidget = handleMirrored();
    }
    else if(newPreprocessing.compare("Grayscale") == 0)
    {
        preprocessingWidget = handleGrayscale();
    }
    connectWidgetDeleteButton(preprocessingWidget->getDeletePreprocessingWidgetButton(), preprocessingWidget);
}

void PreprocessingViewer::connectWidgetDeleteButton(QPushButton *deletePreprocessingWidgetButton, PreprocessingWidget* preprocessingWidgetToDelete)
{
    connect(deletePreprocessingWidgetButton, &QPushButton::released, [=](){this->handleDeletePreprocessingWidgetButton(preprocessingWidgetToDelete);});
}

void PreprocessingViewer::handleDeletePreprocessingWidgetButton(PreprocessingWidget *preprocessingWidgetToDelete)
{
    int index = 0;
    for(PreprocessingWidget *preprocessingWidget : preprocessingWidgetList)
    {
        if(preprocessingWidget == preprocessingWidgetToDelete)
        {
            preprocessingList.erase(preprocessingList.begin() + index);
            preprocessingWidgetList.erase(preprocessingWidgetList.begin() + index);
            preprocessingWidget->deleteMainWidgetGroupBox();
            //should we delete the two objects ?
        }
        index++;
    }
}

MirroredWidget* PreprocessingViewer::handleMirrored()
{
    Mirrored *newMirroredPreprocess = new Mirrored();
    preprocessingList.push_back(newMirroredPreprocess);
    MirroredWidget *newMirroredWidget = new MirroredWidget(mainLayout, this, newMirroredPreprocess);
    preprocessingWidgetList.push_back(newMirroredWidget);
    newMirroredWidget->displayUI();
    return newMirroredWidget;
}

GrayscaleWidget* PreprocessingViewer::handleGrayscale()
{
    Grayscale *newGrayscalePreprocess = new Grayscale();
    preprocessingList.push_back(newGrayscalePreprocess);
    GrayscaleWidget *newGrayscaleWidget = new GrayscaleWidget(mainLayout, this, newGrayscalePreprocess);
    preprocessingWidgetList.push_back(newGrayscaleWidget);
    newGrayscaleWidget->displayUI();
    return newGrayscaleWidget;
}