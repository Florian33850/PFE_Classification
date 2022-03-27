//     PFE_Classification --- Generic classification software
//     Copyright © <2022> Florian Dayre <florian.dayre33850@gmail.com>
//     Copyright © <2022> Élodie Gaudry <elodie.gaudry@etu.u-bordeaux.fr>
//     Copyright © <2022> Hugo Lecomte <hugolecomte932@protonmail.com>
//     Copyright © <2022> Hugo Trarieux <htrarieux@gmail.com>

//     This program is free software: you can redistribute it and/or modify
//     it under the terms of the GNU General Public License as published by
//     the Free Software Foundation, either version 3 of the License, or
//     any later version.

//     This program is distributed in the hope that it will be useful,
//     but WITHOUT ANY WARRANTY; without even the implied warranty of
//     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//     GNU General Public License for more details.

//     You should have received a copy of the GNU General Public License
//     along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "data_augmentation_widget.h"

DataAugmentationWidget::DataAugmentationWidget(QWidget *parentWidget)
    : QWidget(parentWidget)
{
    this->mainLayout = new QVBoxLayout();
    setLayout(this->mainLayout);
    this->parentWidget = parentWidget;
    QLabel *widgetTitle = new QLabel("Data Augmentation");
    this->mainLayout->addWidget(widgetTitle);
    this->addPreviewButton();
    this->addMirrorCheckBox();
    this->addGrayscaleCheckBox();
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
    connect(this->mirrorCheckBox, &QCheckBox::clicked, this, [=]{DataAugmentationWidget::handleImageTransformationCheckBox(this->mirrorWidget, this->mirrorCheckBox, transformationWidgetsEnum::mirror);});
}

void DataAugmentationWidget::addGrayscaleCheckBox()
{
    this->grayscaleCheckBox = new QCheckBox("Grayscale");
    this->mainLayout->addWidget(this->grayscaleCheckBox);
    connect(this->grayscaleCheckBox, &QCheckBox::clicked, this, [=]{DataAugmentationWidget::handleImageTransformationCheckBox(this->grayscaleWidget, this->grayscaleCheckBox, transformationWidgetsEnum::grayscale);});
}

void DataAugmentationWidget::deleteImageTransformationWidget(ImageTransformationWidget *imageTransformationWidget)
{
    for(int index = 0; index < (int) this->imageTransformationWidgetList.size(); index++)
    {
        ImageTransformationWidget *currentImageTransformation = this->imageTransformationWidgetList.at(index);
        if(imageTransformationWidget == currentImageTransformation)
        {
            this->imageTransformationWidgetList.erase(this->imageTransformationWidgetList.begin() + index);
        }
    }
    delete imageTransformationWidget->imageTransformation;
    imageTransformationWidget->deleteMainWidgetGroupBox();
    delete imageTransformationWidget;
}

ImageTransformationWidget* DataAugmentationWidget::initialiseImageTransformationWidget(transformationWidgetsEnum index)
{
    ImageTransformationWidget *imageTransformationWidget = NULL;
    if (index == transformationWidgetsEnum::mirror)
    {
        MirrorImageTransformation *mirrorImageTransformation = new MirrorImageTransformation();
        imageTransformationWidget = new MirrorWidget(this->mainLayout, this->parentWidget, mirrorImageTransformation);
    } 
    else if (index == transformationWidgetsEnum::grayscale)
    {
        GrayscaleImageTransformation *grayscaleImageTransformation = new GrayscaleImageTransformation();
        imageTransformationWidget = new GrayscaleWidget(this->mainLayout, this->parentWidget, grayscaleImageTransformation);
    }
    return imageTransformationWidget;
}

void DataAugmentationWidget::handleImageTransformationCheckBox(ImageTransformationWidget *imageTransformationWidget, QCheckBox *imageTransformationCheckbox, transformationWidgetsEnum index)
{
    if(imageTransformationCheckbox->isChecked())
    {
        imageTransformationWidget = initialiseImageTransformationWidget(index);
        imageTransformationWidgetList.push_back(imageTransformationWidget);
        connect(imageTransformationWidget->getDeleteImageTransformationWidgetButton(), &QPushButton::released, this,
            [=]{handleDeleteImageTransformationWidgetButton(imageTransformationWidget, imageTransformationCheckbox);});
        imageTransformationWidget->displayUI(this->mainLayout->indexOf(imageTransformationCheckbox) + 1);
    }
    else
    {
        // Segfault when trying to call the next commented function and imageTransformationCheckbox try to uncheck
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
