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

#include <QtTest/QtTest>

#include "../src/data_augmentation_tab.h"

class DataAugmentationTabTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testDataAugmentationTabInstantiation();
        void testNewDataHandler();
};

void DataAugmentationTabTests::testDataAugmentationTabInstantiation()
{
    DataAugmentationTab *dataAugmentationTab = new DataAugmentationTab();
    QVERIFY(dataAugmentationTab != NULL);
}

void DataAugmentationTabTests::testNewDataHandler()
{
    DataAugmentationTab *dataAugmentationTab = new DataAugmentationTab();
    
    QWidget *parent1 = NULL;
    std::vector<ImageLabel*> *imagePreviewList1 = new std::vector<ImageLabel*>();
    ImageSelectionHandler *imageSelectionHandler = new ImageSelectionHandler(parent1, imagePreviewList1);

    QWidget *parent2 = NULL;
    std::vector<ImageLabel*> *imagePreviewList2 = new std::vector<ImageLabel*>();
    LymeDatabaseHandler *lymeDatabaseHandler = new LymeDatabaseHandler(parent2, imagePreviewList2);

    dataAugmentationTab->handleNewDataHandler(imageSelectionHandler);
    QVERIFY(dataAugmentationTab->dataHandler == imageSelectionHandler);

    dataAugmentationTab->handleNewDataHandler(lymeDatabaseHandler);
    QVERIFY(dataAugmentationTab->dataHandler == lymeDatabaseHandler);
}

QTEST_MAIN(DataAugmentationTabTests)
#include "data_augmentation_tab_test.moc"
