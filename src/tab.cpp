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

#include "tab.h"

#include <iostream>

Tab::Tab()
{
    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(TAB_MAIN_LAYOUT_SPACING);
    this->mainLayout->setMargin(TAB_MAIN_LAYOUT_MARGIN);
    this->setLayout(this->mainLayout);
}

Tab::~Tab() {}

void Tab::handleSaveButton(QString pathToSave)
{
    QMessageBox saveStartMessage;
    saveStartMessage.setWindowTitle("Information");
    saveStartMessage.setText("Data Base is saving...");
    saveStartMessage.exec();

    if(this->dataHandler->saveImagesInFile(this->imageTransformationViewer->getImageTransformationWidgetList(), pathToSave))
    {
        QMessageBox saveEndMessage;
        saveEndMessage.setWindowTitle("Information");
        saveEndMessage.setText("Data Base correctly saved.");
        saveEndMessage.exec();
    }
}
