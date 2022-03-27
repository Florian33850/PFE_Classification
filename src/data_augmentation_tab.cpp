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

#include "data_augmentation_tab.h"

DataAugmentationTab::DataAugmentationTab() : Tab()
{
    this->imagePreviewList = new std::vector<ImageLabel*>();
    this->imageTransformationViewer = new DataAugmentationViewer(this->imagePreviewList);
    this->imagesPreviewWidget = new ImagesPreviewWidget(this->imagePreviewList, this->imageTransformationViewer);
    connect(this->imageTransformationViewer, &ImageTransformationViewer::reloadPreviewSignal, this->imagesPreviewWidget, &ImagesPreviewWidget::reloadPreview);
    this->mainLayout->addWidget(this->imagesPreviewWidget, ROW_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET, COLUMN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET,
                                ROW_SPAN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET, COLUMN_SPAN_DATA_AUGMENTATION_TAB_IMAGES_PREVIEW_WIDGET);
    this->mainLayout->addWidget(this->imageTransformationViewer, ROW_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER, COLUMN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER,
                                ROW_SPAN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER, COLUMN_SPAN_DATA_AUGMENTATION_TAB_TRANSFORMATION_VIEWER);
    this->addSaveButton();
    this->addDataBaseCountDisplay();
}

void DataAugmentationTab::addSaveButton()
{
    QPushButton *saveImagesButton = new QPushButton("&Save");
    connect(saveImagesButton, &QPushButton::released, [=](){this->handleSaveButton("/savedData/Data_Augmentation");});
    this->mainLayout->addWidget(saveImagesButton, ROW_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON, COLUMN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON,
                                ROW_SPAN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON, COLUMN_SPAN_DATA_AUGMENTATION_TAB_SAVE_IMAGES_BUTTON);
}

void DataAugmentationTab::handleNewDataHandler(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    this->dataHandler->loadNextPreview();
    this->imagesPreviewWidget->display(this->dataHandler);
    this->refreshDataBaseCountDisplay();
}

void DataAugmentationTab::addDataBaseCountDisplay()
{
    this->dataBaseCountLayout = new QVBoxLayout();
    this->originalImagesLabel = new QLabel();
    this->dataBaseCountLayout->insertWidget(this->dataBaseCountLayout->count()-1, originalImagesLabel);
    this->mainLayout->addLayout(dataBaseCountLayout, ROW_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT, COLUMN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT,
                                ROW_SPAN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT, COLUMN_SPAN_DATA_AUGMENTATION_TAB_DATABASE_COUNT_LAYOUT);
}

void DataAugmentationTab::refreshDataBaseCountDisplay()
{
    QString numberOriginalImages = QString::number(dataHandler->pathToImages.size());
    this->originalImagesLabel->setText("Original images: " + numberOriginalImages);
}
