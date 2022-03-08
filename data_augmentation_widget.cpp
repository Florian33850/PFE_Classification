#include "data_augmentation_widget.h"

DataAugmentationWidget::DataAugmentationWidget(QWidget *parentWidget)
{
    this->mainLayout = new QVBoxLayout();
    setLayout(this->mainLayout);
    this->parentWidget = parentWidget;
    QLabel *widgetTitle = new QLabel("DataAugmentation 1");
    this->mainLayout->addWidget(widgetTitle);
    addPreviewButton();
    addMirrorCheckBox();
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
    connect(mirrorCheckBox, &QCheckBox::clicked, this, &DataAugmentationWidget::handleMirrorCheckbox);
}

void DataAugmentationWidget::deleteImageTransformationWidget(ImageTransformationWidget *imageTransformationWidget)
{
    int index = 0;
    for(ImageTransformation *currentImageTransformation : this->imageTransformationList)
    {
        if(this->mirrorWidget->imageTransformation == currentImageTransformation)
        {
            this->imageTransformationList.erase(this->imageTransformationList.begin() + index);
        }
        index++;
    }
    delete this->mirrorWidget->imageTransformation;
    this->mirrorWidget->deleteMainWidgetGroupBox();
    delete this->mirrorWidget;
}

void DataAugmentationWidget::handleMirrorCheckbox()
{
    if(this->mirrorCheckBox->isChecked())
    {
        MirrorImageTransformation *mirrorImageTransformation = new MirrorImageTransformation();
        imageTransformationList.push_back(mirrorImageTransformation);
        this->mirrorWidget = new MirrorWidget(this->mainLayout, parentWidget, mirrorImageTransformation);
        connect(this->mirrorWidget->getDeleteImageTransformationWidgetButton(), &QPushButton::released, this, 
            &DataAugmentationWidget::handleDeleteImageTransformationWidgetButton);
        this->mirrorWidget->displayUI(this->mainLayout->indexOf(this->mirrorCheckBox) + 1);
    }
    else
    {
        deleteImageTransformationWidget(this->mirrorWidget);
    }
}

void DataAugmentationWidget::handleDeleteImageTransformationWidgetButton()
{
    this->deleteImageTransformationWidget(this->mirrorWidget);
    this->mirrorCheckBox->setCheckState(Qt::Unchecked);
}


void DataAugmentationWidget::handlePreviewButton()
{
    printf("teststetdtsdtst\n");
}