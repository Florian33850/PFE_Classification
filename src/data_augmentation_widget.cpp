#include "data_augmentation_widget.h"

DataAugmentationWidget::DataAugmentationWidget(QWidget *parentWidget)
    : QWidget(parentWidget)
{
    this->mainLayout = new QVBoxLayout();
    setLayout(this->mainLayout);
    this->parentWidget = parentWidget;
    QLabel *widgetTitle = new QLabel("Data Augmentation");
    this->mainLayout->addWidget(widgetTitle);
    addPreviewButton();
    addMirrorCheckBox();
    addGrayscaleCheckBox();
}

void DataAugmentationWidget::addPreviewButton()
{
    this->previewButton = new QPushButton("Preview");
    connect(this->previewButton, &QPushButton::released, this, &DataAugmentationWidget::handlePreviewButton);
    this->mainLayout->insertWidget(this->mainLayout->count()-1, this->previewButton);
}

void DataAugmentationWidget::addMirrorCheckBox()
{
    this->mirrorCheckBox = new QCheckBox("Mirror");
    this->mainLayout->addWidget(this->mirrorCheckBox);
    connect(mirrorCheckBox, &QCheckBox::clicked, this, [=]{DataAugmentationWidget::handleImageTransformationCheckBox(this->mirrorWidget, this->mirrorCheckBox, transformationWidgetsEnum::mirror);});
}

void DataAugmentationWidget::addGrayscaleCheckBox()
{
    this->grayscaleCheckBox = new QCheckBox("Grayscale");
    this->mainLayout->addWidget(this->grayscaleCheckBox);
    connect(grayscaleCheckBox, &QCheckBox::clicked, this, [=]{DataAugmentationWidget::handleImageTransformationCheckBox(this->grayscaleWidget, this->grayscaleCheckBox, transformationWidgetsEnum::grayscale);});
}

void DataAugmentationWidget::deleteImageTransformationWidget(ImageTransformationWidget *imageTransformationWidget)
{
    int index = 0;
    for(ImageTransformationWidget *currentImageTransformation : this->imageTransformationWidgetList)
    {
        if(imageTransformationWidget == currentImageTransformation)
        {
            this->imageTransformationWidgetList.erase(this->imageTransformationWidgetList.begin() + index);
        }
        index++;
    }
    delete imageTransformationWidget->imageTransformation;
    imageTransformationWidget->deleteMainWidgetGroupBox();
    delete imageTransformationWidget;
}

ImageTransformationWidget* DataAugmentationWidget::initialiseImageTransformationWidget(ImageTransformationWidget *imageTransformationWidget, transformationWidgetsEnum index)
{
    if (index == transformationWidgetsEnum::mirror) {
        MirrorImageTransformation *mirrorImageTransformation = new MirrorImageTransformation();
        imageTransformationWidget = new MirrorWidget(this->mainLayout, parentWidget, mirrorImageTransformation);
        return imageTransformationWidget;
    } else if (index == transformationWidgetsEnum::grayscale) {
        GrayscaleImageTransformation *grayscaleImageTransformation = new GrayscaleImageTransformation();
        imageTransformationWidget = new GrayscaleWidget(this->mainLayout, parentWidget, grayscaleImageTransformation);
        return imageTransformationWidget;
    } else {
        return NULL;
    }
}

void DataAugmentationWidget::handleImageTransformationCheckBox(ImageTransformationWidget *imageTransformationWidget, QCheckBox *imageTransformationCheckbox, transformationWidgetsEnum index)
{
    if(imageTransformationCheckbox->isChecked())
    {
        imageTransformationWidget = initialiseImageTransformationWidget(imageTransformationWidget, index);
        imageTransformationWidgetList.push_back(imageTransformationWidget);
        connect(imageTransformationWidget->getDeleteImageTransformationWidgetButton(), &QPushButton::released, this,
            [=]{handleDeleteImageTransformationWidgetButton(imageTransformationWidget, imageTransformationCheckbox);});
        imageTransformationWidget->displayUI(this->mainLayout->indexOf(imageTransformationCheckbox) + 1);
    }
    else
    {
        // segfault when trying to call the next commented function and imageTransformationCheckbox try to uncheck
        //this->deleteImageTransformationWidget(imageTransformationWidget);
    }
}


void DataAugmentationWidget::handleDeleteImageTransformationWidgetButton(ImageTransformationWidget *imageTransformationWidget, QCheckBox *imageTransformationCheckbox)
{
    this->deleteImageTransformationWidget(imageTransformationWidget);
    imageTransformationCheckbox->setCheckState(Qt::Unchecked);
}

void DataAugmentationWidget::handlePreviewButton()
{
    Q_EMIT previewSignal(this);
}