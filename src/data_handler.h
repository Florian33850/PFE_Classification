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

#ifndef data_handler_H
#define data_handler_H

#include "image_transformation_widget.h"
#include "constants.h"

#include <iostream>
#include <unistd.h>
#include <QStringList>
#include <QFileDialog>
#include <QDirIterator>
#include <QDir>

class DataHandler
{
    public:
        DataHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        QStringList pathToImages;
        int maxNumberOfImagesToLoad;
        int totalNumberOfImages;
        int indexPathToImagesList;

        bool reloadPreview();
        bool loadNextPreview();
        bool loadPreviousPreview();

        virtual bool selectDataBasePath() = 0;
        virtual bool saveImagesInFile(std::vector<ImageTransformationWidget*> imageTransformationWidgetList, QString saveFolderName = "") = 0;

    protected:
        QWidget *parent;
        std::vector<ImageLabel*> *imagePreviewList;

        void addImageToImagePreviewList(QImage qImage);
};

class ImageSelectionHandler : public DataHandler
{
    public:
        ImageSelectionHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();
        bool saveImagesInFile(std::vector<ImageTransformationWidget*> imageTransformationWidgetList, QString saveFolderName = "");
};

class LymeDatabaseHandler : public DataHandler
{
    public:
        LymeDatabaseHandler(QWidget *parent, std::vector<ImageLabel*> *imagePreviewList);

        bool selectDataBasePath();
        bool saveImagesInFile(std::vector<ImageTransformationWidget*> imageTransformationWidgetList, QString saveFolderName = "");

    private:
        QString pathToDatabase;
};
#endif //data_handler_H
