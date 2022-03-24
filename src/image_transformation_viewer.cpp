#include "image_transformation_viewer.h"

ImageTransformationViewer::ImageTransformationViewer(std::vector<ImageLabel*> *imagePreviewList, QWidget *parentWidget)
    : QWidget(parentWidget)
{
    this->mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);
    this->mainLayout->setSpacing(MAIN_LAYOUT_SPACING_IMAGE_TRANSFORMATION_VIEWER);
    this->mainLayout->setMargin(MAIN_LAYOUT_MARGIN_IMAGE_TRANSFORMATION_VIEWER);

    this->imagePreviewList = imagePreviewList;

    this->mainLayout->addStretch();
}

void ImageTransformationViewer::launchActivatedPreprocesses()
{
    for(ImageTransformationWidget *imageTransformationWidget : this->imageTransformationWidgetList)
    {
        if(imageTransformationWidget->isActivated)
        {
            imageTransformationWidget->imageTransformation->runImageTransformationOnPreviewList(this->imagePreviewList);
        }
    }
}

MirrorWidget* ImageTransformationViewer::createMirrorImageTransformation()
{
    MirrorImageTransformation *newMirrorImageTransformation = new MirrorImageTransformation();
    this->imageTransformationList.push_back(newMirrorImageTransformation);

    MirrorWidget *newMirrorWidget = new MirrorWidget(this->mainLayout, this, newMirrorImageTransformation);
    this->imageTransformationWidgetList.push_back(newMirrorWidget);

    newMirrorWidget->displayUI(newMirrorWidget->getLayoutCount()-1);
    return newMirrorWidget;
}

GrayscaleWidget* ImageTransformationViewer::createGrayscaleImageTransformation()
{
    GrayscaleImageTransformation *newGrayscaleImageTransformation = new GrayscaleImageTransformation();
    this->imageTransformationList.push_back(newGrayscaleImageTransformation);

    GrayscaleWidget *newGrayscaleWidget = new GrayscaleWidget(this->mainLayout, this, newGrayscaleImageTransformation);
    this->imageTransformationWidgetList.push_back(newGrayscaleWidget);

    newGrayscaleWidget->displayUI(newGrayscaleWidget->getLayoutCount()-1);
    return newGrayscaleWidget;
}

AutomaticRotationLymeDataWidget* ImageTransformationViewer::createAutomaticRotationLymeDataImageTransformation()
{
    AutomaticRotationLymeDataImageTransformation *newAutomaticRotationImageTransformation = new AutomaticRotationLymeDataImageTransformation();
    this->imageTransformationList.push_back(newAutomaticRotationImageTransformation);

    AutomaticRotationLymeDataWidget *newAutomaticRotationWidget = new AutomaticRotationLymeDataWidget(this->mainLayout, this, newAutomaticRotationImageTransformation);
    this->imageTransformationWidgetList.push_back(newAutomaticRotationWidget);

    newAutomaticRotationWidget->displayUI(newAutomaticRotationWidget->getLayoutCount()-1);
    return newAutomaticRotationWidget;
}

MorphologicalTransformationWidget* ImageTransformationViewer::createMorphologicalTransformationImageTransformation()
{
    MorphologicalTransformationImageTransformation *newMorphologicalTransformationImageTransformation = new MorphologicalTransformationImageTransformation();
    this->imageTransformationList.push_back(newMorphologicalTransformationImageTransformation);

    MorphologicalTransformationWidget *newMorphologicalTransformationWidget = new MorphologicalTransformationWidget(this->mainLayout, this, newMorphologicalTransformationImageTransformation);
    this->imageTransformationWidgetList.push_back(newMorphologicalTransformationWidget);

    newMorphologicalTransformationWidget->displayUI(newMorphologicalTransformationWidget->getLayoutCount()-1);
    return newMorphologicalTransformationWidget;
}

void ImageTransformationViewer::handleLaunchImageTransformationButton()
{
    if(!this->imageTransformationWidgetList.empty())
    {
        Q_EMIT reloadPreviewSignal();
    }
    for(ImageTransformationWidget *imageTransformationWidget : this->imageTransformationWidgetList)
    {
        imageTransformationWidget->isActivated = true;
    }
    this->launchActivatedPreprocesses();
}

std::vector<ImageTransformationWidget*> ImageTransformationViewer::getImageTransformationWidgetList(){
    return this->imageTransformationWidgetList;
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
    else if(newImageTransformation.compare("Automatic Rotation for Lyme Data") == 0)
    {
        imageTransformationWidget = createAutomaticRotationLymeDataImageTransformation();
    }
    else if(newImageTransformation.compare("Morphological Transformation") == 0)
    {
        imageTransformationWidget = createMorphologicalTransformationImageTransformation();
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
    addAddDataAugmentationButton();
}

void DataAugmentationViewer::addAddDataAugmentationButton()
{
    this->addDataAugmentationButton = new QPushButton("Add Data Augmentation");
    connect(this->addDataAugmentationButton, &QPushButton::released, this, &DataAugmentationViewer::handleAddDataAugmentationButton);
    this->mainLayout->insertWidget(this->mainLayout->count()-1, this->addDataAugmentationButton);
}

void DataAugmentationViewer::handleAddDataAugmentationButton()
{
    DataAugmentationWidget *dataAugmentationWidgetToAdd = new DataAugmentationWidget(this);
    connect(dataAugmentationWidgetToAdd, SIGNAL(previewSignal(DataAugmentationWidget*)), this, SLOT(handlePreview(DataAugmentationWidget*)));
    this->mainLayout->insertWidget(this->mainLayout->count()-1, dataAugmentationWidgetToAdd);
}

void DataAugmentationViewer::handlePreview(DataAugmentationWidget* sender)
{
    if(!this->imagePreviewList->empty())
    {
        this->imageTransformationWidgetList = sender->imageTransformationWidgetList;
        handleLaunchImageTransformationButton();
    }
}