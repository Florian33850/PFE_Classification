#include "image_transformation_viewer.h"

ImageTransformationViewer::ImageTransformationViewer(std::vector<ImageLabel*> *imagePreviewList, QWidget *parentWidget)
    : QWidget(parentWidget)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->mainLayout->setSpacing(1);
    this->mainLayout->setMargin(1);

    this->imagePreviewList = imagePreviewList;

    this->mainLayout->addStretch();
}

void ImageTransformationViewer::launchActivatedPreprocesses()
{
    for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
    {
        if(imageTransformationWidget->isActivated)
        {
            imageTransformationWidget->imageTransformation->runImageTransformation(imagePreviewList);
        }
    }
}

MirrorWidget* ImageTransformationViewer::createMirrorImageTransformation()
{
    MirrorImageTransformation *newMirrorImageTransformation = new MirrorImageTransformation();
    imageTransformationList.push_back(newMirrorImageTransformation);

    MirrorWidget *newMirrorWidget = new MirrorWidget(mainLayout, this, newMirrorImageTransformation);
    imageTransformationWidgetList.push_back(newMirrorWidget);

    newMirrorWidget->displayUI();
    return newMirrorWidget;
}

GrayscaleWidget* ImageTransformationViewer::createGrayscaleImageTransformation()
{
    GrayscaleImageTransformation *newGrayscaleImageTransformation = new GrayscaleImageTransformation();
    imageTransformationList.push_back(newGrayscaleImageTransformation);

    GrayscaleWidget *newGrayscaleWidget = new GrayscaleWidget(mainLayout, this, newGrayscaleImageTransformation);
    imageTransformationWidgetList.push_back(newGrayscaleWidget);

    newGrayscaleWidget->displayUI();
    return newGrayscaleWidget;
}

void ImageTransformationViewer::handleLaunchImageTransformationButton()
{
    for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
    {
        imageTransformationWidget->isActivated = true;
    }
    launchActivatedPreprocesses();
}


void ImageTransformationViewer::handleDeleteImageTransformationWidgetButton(ImageTransformationWidget *imageTransformationWidgetToDelete)
{
    int index = 0;
    for(ImageTransformationWidget *imageTransformationWidget : imageTransformationWidgetList)
    {
        if(imageTransformationWidget == imageTransformationWidgetToDelete)
        {
            imageTransformationList.erase(imageTransformationList.begin() + index);
            imageTransformationWidgetList.erase(imageTransformationWidgetList.begin() + index);
            imageTransformationWidget->deleteMainWidgetGroupBox();
            delete imageTransformationWidget;
        }
        index++;
    }
}


PreprocessingViewer::PreprocessingViewer(std::vector<ImageLabel*> *imagePreviewList, QWidget *parentWidget)
    : ImageTransformationViewer(imagePreviewList, parentWidget)
{
    addLaunchPreprocessingButton();
    addAddPreprocessingComboBox();
}

void PreprocessingViewer::addLaunchPreprocessingButton()
{
    this->launchPreprocessingButton = new QPushButton("Launch preprocessing");
    connect(this->launchPreprocessingButton, &QPushButton::released, this, &PreprocessingViewer::handleLaunchImageTransformationButton);
    this->mainLayout->insertWidget(this->mainLayout->count()-1, this->launchPreprocessingButton);
}

void PreprocessingViewer::addAddPreprocessingComboBox()
{
    this->addPreprocessingComboBox = new QComboBox();
    this->addPreprocessingComboBox->addItems(preprocessingStringList);
    connect(this->addPreprocessingComboBox, QOverload<int>::of(&QComboBox::activated), this, &PreprocessingViewer::handleImageTransformationComboBox);
    this->mainLayout->insertWidget(this->mainLayout->count()-1, addPreprocessingComboBox);
}

void PreprocessingViewer::handleImageTransformationComboBox()
{
    QString newImageTransformation = this->addPreprocessingComboBox->currentText();
    ImageTransformationWidget *imageTransformationWidget;
    if(newImageTransformation.compare("Mirror") == 0)
    {
        imageTransformationWidget = createMirrorImageTransformation();
    }
    else if(newImageTransformation.compare("Grayscale") == 0)
    {
        imageTransformationWidget = createGrayscaleImageTransformation();
    }
    else
    {
        return;
    }
    connect(imageTransformationWidget->getDeleteImageTransformationWidgetButton(), &QPushButton::released, 
        [=](){this->handleDeleteImageTransformationWidgetButton(imageTransformationWidget);});
}

DataAugmentationViewer::DataAugmentationViewer(std::vector<ImageLabel*> *imagePreviewList, QWidget *parentWidget)
    : ImageTransformationViewer(imagePreviewList, parentWidget)
{
}