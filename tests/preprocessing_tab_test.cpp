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

#include "../src/preprocessing_tab.h"

class PreprocessingTabTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testPreprocessingTabInstantiation();
        void testPreprocessingTabNewDataHandler();
};

void PreprocessingTabTests::testPreprocessingTabInstantiation()
{
    PreprocessingTab *preprocessingTab = new PreprocessingTab();
    QVERIFY(preprocessingTab != NULL);
}

void PreprocessingTabTests::testPreprocessingTabNewDataHandler()
{
    PreprocessingTab *preprocessingTab = new PreprocessingTab();

    QWidget *parent1 = NULL;
    std::vector<ImageLabel*> *imagePreviewList1 = new std::vector<ImageLabel*>();
    ImageSelectionHandler *dataHandler1 = new ImageSelectionHandler(parent1, imagePreviewList1);

    QWidget *parent2 = NULL;
    std::vector<ImageLabel*> *imagePreviewList2 = new std::vector<ImageLabel*>();
    LymeDatabaseHandler *dataHandler2 = new LymeDatabaseHandler(parent2, imagePreviewList2);

    preprocessingTab->handleNewDataHandler(dataHandler1);
    QVERIFY(preprocessingTab->dataHandler == dataHandler1);
    preprocessingTab->handleNewDataHandler(dataHandler2);
    QVERIFY(preprocessingTab->dataHandler == dataHandler2);
}

QTEST_MAIN(PreprocessingTabTests)
#include "preprocessing_tab_test.moc"
