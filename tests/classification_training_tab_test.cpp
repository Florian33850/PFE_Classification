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

#include "../src/classification_training_tab.h"

class ClassificationTrainingTabTests: public QObject
{
    Q_OBJECT

    private:

    private Q_SLOTS:
        void testClassificationTrainingTabInstantiation();
};

void ClassificationTrainingTabTests::testClassificationTrainingTabInstantiation()
{
    ClassificationTrainingTab *classificationTrainingTab = new ClassificationTrainingTab();
    QVERIFY(classificationTrainingTab != NULL);
}

QTEST_MAIN(ClassificationTrainingTabTests)
#include "classification_training_tab_test.moc"
