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

    QStringList preprocessingList = {"Add Preprocessing", "Mirror", "Grayscale"};
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
    if(newPreprocessing.compare("Mirror") == 0)
    {
        preprocessingWidget = addMirrorPreprocess();
    }
    else if(newPreprocessing.compare("Grayscale") == 0)
    {
        preprocessingWidget = addGrayscalePreprocess();
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
        }
        index++;
    }
}

MirrorWidget* PreprocessingViewer::addMirrorPreprocess()
{
    MirrorPreprocess *newMirrorPreprocess = new MirrorPreprocess();
    preprocessingList.push_back(newMirrorPreprocess);
    MirrorWidget *newMirrorWidget = new MirrorWidget(mainLayout, this, newMirrorPreprocess);
    preprocessingWidgetList.push_back(newMirrorWidget);
    newMirrorWidget->displayUI();
    return newMirrorWidget;
}

GrayscaleWidget* PreprocessingViewer::addGrayscalePreprocess()
{
    GrayscalePreprocess *newGrayscalePreprocess = new GrayscalePreprocess();
    preprocessingList.push_back(newGrayscalePreprocess);
    GrayscaleWidget *newGrayscaleWidget = new GrayscaleWidget(mainLayout, this, newGrayscalePreprocess);
    preprocessingWidgetList.push_back(newGrayscaleWidget);
    newGrayscaleWidget->displayUI();
    return newGrayscaleWidget;
}