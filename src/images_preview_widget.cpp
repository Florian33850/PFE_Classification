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

#include "images_preview_widget.h"

ImagesPreviewWidget::ImagesPreviewWidget(std::vector<ImageLabel*> *imagePreviewList, ImageTransformationViewer *imageTransformationViewer){
    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(IMAGES_PREVIEW_MAIN_LAYOUT_SPACING);
    this->mainLayout->setMargin(IMAGES_PREVIEW_MAIN_LAYOUT_MARGIN);

    this->imagesLayout = new QGridLayout();
    this->mainLayout->addLayout(imagesLayout, ROW_IMAGES_PREVIEW_IMAGES_LAYOUT, COLUMN_IMAGES_PREVIEW_IMAGES_LAYOUT,
                                            ROW_SPAN_IMAGES_PREVIEW_IMAGES_LAYOUT, COLUMN_SPAN_IMAGES_PREVIEW_IMAGES_LAYOUT);

    this->imageTransformationViewer = imageTransformationViewer;
    this->imagePreviewList = imagePreviewList;
    this->dataHandler = dataHandler;
    this->setLayout(this->mainLayout);
}

void ImagesPreviewWidget::display(DataHandler *dataHandler)
{
    this->dataHandler = dataHandler;
    clearLayout(this->imagesLayout);
    displayDataBasePreview();
    addPreviousPreviewButton();
    addNextPreviewButton();
}

void ImagesPreviewWidget::displayDataBasePreview()
{
    int imageIndex = 0;
    int previewListSize = imagePreviewList->size();
    for(int row = 0; row < IMAGES_PREVIEW_MAXIMUM_ROWS; row++)
    {
        for(int col = 0; col < IMAGES_PREVIEW_MAXIMUM_COLLUMNS; col++)
        {
            if(imageIndex >= this->dataHandler->maxNumberOfImagesToLoad || imageIndex >= previewListSize)
            {
                break;
            }
            this->imagesLayout->addWidget(this->imagePreviewList->at(imageIndex), row, col);
            imageIndex++;
        }
    }
}

void ImagesPreviewWidget::addPreviousPreviewButton()
{
    QPushButton *previousDataBasePreview = new QPushButton("Prev");
    connect(previousDataBasePreview, &QPushButton::released, this, &ImagesPreviewWidget::handleLoadPreviousPreviewButton);
    this->mainLayout->addWidget(previousDataBasePreview, ROW_IMAGES_PREVIEW_PREVIOUS_BUTTON, COLUMN_IMAGES_PREVIEW_PREVIOUS_BUTTON,
                                                        ROW_SPAN_IMAGES_PREVIEW_PREVIOUS_BUTTON, COLUMN_SPAN_IMAGES_PREVIEW_PREVIOUS_BUTTON);
}

void ImagesPreviewWidget::addNextPreviewButton()
{
    QPushButton *nextDataBasePreview = new QPushButton("Next");
    connect(nextDataBasePreview, &QPushButton::released, this, &ImagesPreviewWidget::handleLoadNextPreviewButton);
    this->mainLayout->addWidget(nextDataBasePreview, ROW_IMAGES_PREVIEW_NEXT_BUTTON, COLUMN_IMAGES_PREVIEW_NEXT_BUTTON,
                                                    ROW_SPAN_IMAGES_PREVIEW_NEXT_BUTTON, COLUMN_SPAN_IMAGES_PREVIEW_NEXT_BUTTON);
}

void ImagesPreviewWidget::reloadPreview()
{
    this->dataHandler->reloadPreview();
    clearLayout(this->imagesLayout);
    displayDataBasePreview();
}

void ImagesPreviewWidget::handleLoadNextPreviewButton()
{
    if(this->dataHandler->loadNextPreview())
    {
        clearLayout(this->imagesLayout);
        this->imageTransformationViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }    
}

void ImagesPreviewWidget::handleLoadPreviousPreviewButton()
{
    if(this->dataHandler->loadPreviousPreview())
    {
        clearLayout(this->imagesLayout);
        this->imageTransformationViewer->launchActivatedPreprocesses();
        displayDataBasePreview();
    }
}
