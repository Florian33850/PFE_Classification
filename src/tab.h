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

#ifndef TAB_H
#define TAB_H

#include "images_preview_widget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>

class Tab : public QWidget
{
    Q_OBJECT
    public:
        Tab();
        ~Tab();

        DataHandler *dataHandler;
        ImagesPreviewWidget *imagesPreviewWidget;
        std::vector<ImageLabel*> *imagePreviewList;

    protected:
        QGridLayout *mainLayout;
        ImageTransformationViewer *imageTransformationViewer;

        void handleSaveButton(QString pathToSave);
        void handleStartSave(QString pathToSave);
        void handleEndSave();
};
#endif // TAB_H
