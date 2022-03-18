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
    for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
    {
        if(imageTransformationWidget->isActivated)
        {
            imageTransformationWidget->imageTransformation->runImageTransformation(imagePreviewList);
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

MirrorWidget* PreprocessingViewer::createMirrorImageTransformation()
{
    MirrorImageTransformation *newMirrorImageTransformation = new MirrorImageTransformation();
    preprocessingList.push_back(newMirrorImageTransformation);

    MirrorWidget *newMirrorWidget = new MirrorWidget(mainLayout, this, newMirrorImageTransformation);
    imageTransformationWidgetList.push_back(newMirrorWidget);

    newMirrorWidget->displayUI();
    return newMirrorWidget;
}

GrayscaleWidget* PreprocessingViewer::createGrayscaleImageTransformation()
{
    GrayscaleImageTransformation *newGrayscaleImageTransformation = new GrayscaleImageTransformation();
    preprocessingList.push_back(newGrayscaleImageTransformation);

    GrayscaleWidget *newGrayscaleWidget = new GrayscaleWidget(mainLayout, this, newGrayscaleImageTransformation);
    imageTransformationWidgetList.push_back(newGrayscaleWidget);

    newGrayscaleWidget->displayUI();
    return newGrayscaleWidget;
}

void PreprocessingViewer::handleLaunchPreprocessingButton()
{
    for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
    {
        imageTransformationWidget->isActivated = true;
    }
    launchActivatedPreprocesses();
}

void PreprocessingViewer::handlePreprocessingComboBox()
{
    QString newPreprocessing = addPreprocessingComboBox->currentText();
    ImageTransformationWidget *imageTransformationWidget;
    if(newPreprocessing.compare("Mirror") == 0)
    {
        imageTransformationWidget = createMirrorImageTransformation();
    }
    else if(newPreprocessing.compare("Grayscale") == 0)
    {
        imageTransformationWidget = createGrayscaleImageTransformation();
    }
    connect(imageTransformationWidget->getDeleteImageTransformationWidgetButton(), &QPushButton::released, 
        [=](){this->handleDeleteImageTransformationWidgetButton(imageTransformationWidget);});
}

void PreprocessingViewer::handleDeleteImageTransformationWidgetButton(ImageTransformationWidget *imageTransformationWidgetToDelete)
{
    int index = 0;
    for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
    {
        if(imageTransformationWidget == imageTransformationWidgetToDelete)
        {
            preprocessingList.erase(preprocessingList.begin() + index);
            imageTransformationWidgetList.erase(imageTransformationWidgetList.begin() + index);
            imageTransformationWidget->deleteMainWidgetGroupBox();
            delete imageTransformationWidget;
        }
        index++;
    }
}