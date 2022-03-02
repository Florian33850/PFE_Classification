#include "preprocessing_viewer.h"

PreprocessingViewer::PreprocessingViewer(std::vector<ImageLabel*> *imagePreviewList, QWidget *parent)
    : QWidget(parent)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->mainLayout->setSpacing(1);
    this->mainLayout->setMargin(1);

    this->imagePreviewList = imagePreviewList;
    addLaunchPreprocessingButton();
    addAddPreprocessingComboBox();

    this->mainLayout->addStretch();
}

void PreprocessingViewer::launchActivatedPreprocesses()
{
    for(PreprocessingWidget *preprocessingWidget : preprocessingWidgetList)
    {
        if(preprocessingWidget->isActivated)
        {
            preprocessingWidget->preprocess->runPreprocess(imagePreviewList);
        }
    }
}

void PreprocessingViewer::addLaunchPreprocessingButton()
{
    this->launchPreprocessingButton = new QPushButton("Launch preprocessing");
    connect(launchPreprocessingButton, &QPushButton::released, this, &PreprocessingViewer::handleLaunchPreprocessingButton);
    mainLayout->addWidget(launchPreprocessingButton);
}

void PreprocessingViewer::addAddPreprocessingComboBox()
{
    addPreprocessingComboBox = new QComboBox();
    addPreprocessingComboBox->addItems(preprocessingStringList);
    connect(addPreprocessingComboBox, QOverload<int>::of(&QComboBox::activated), this, &PreprocessingViewer::handlePreprocessingComboBox);
    mainLayout->addWidget(addPreprocessingComboBox);
}

MirrorWidget* PreprocessingViewer::createMirrorPreprocess()
{
    MirrorPreprocess *newMirrorPreprocess = new MirrorPreprocess();
    preprocessingList.push_back(newMirrorPreprocess);

    MirrorWidget *newMirrorWidget = new MirrorWidget(mainLayout, this, newMirrorPreprocess);
    preprocessingWidgetList.push_back(newMirrorWidget);

    newMirrorWidget->displayUI();
    return newMirrorWidget;
}

GrayscaleWidget* PreprocessingViewer::createGrayscalePreprocess()
{
    GrayscalePreprocess *newGrayscalePreprocess = new GrayscalePreprocess();
    preprocessingList.push_back(newGrayscalePreprocess);

    GrayscaleWidget *newGrayscaleWidget = new GrayscaleWidget(mainLayout, this, newGrayscalePreprocess);
    preprocessingWidgetList.push_back(newGrayscaleWidget);

    newGrayscaleWidget->displayUI();
    return newGrayscaleWidget;
}

void PreprocessingViewer::handleLaunchPreprocessingButton()
{
    for(PreprocessingWidget *preprocessingWidget : preprocessingWidgetList)
    {
        preprocessingWidget->isActivated = true;
    }
    launchActivatedPreprocesses();
}

void PreprocessingViewer::handlePreprocessingComboBox()
{
    QString newPreprocessing = addPreprocessingComboBox->currentText();
    PreprocessingWidget *preprocessingWidget;
    if(newPreprocessing.compare("Mirror") == 0)
    {
        preprocessingWidget = createMirrorPreprocess();
    }
    else if(newPreprocessing.compare("Grayscale") == 0)
    {
        preprocessingWidget = createGrayscalePreprocess();
    }
    connect(preprocessingWidget->getDeletePreprocessingWidgetButton(), &QPushButton::released, 
        [=](){this->handleDeletePreprocessingWidgetButton(preprocessingWidget);});
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
            delete preprocessingWidget;
        }
        index++;
    }
}