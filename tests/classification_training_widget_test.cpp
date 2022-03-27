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

#include "../src/classification_training_widget.h"

class ClassificationTrainingWidgetTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testDeepLearningWidgetInstantiation();
        void testRandomForestWidgetInstantiation();
};

void ClassificationTrainingWidgetTests::testDeepLearningWidgetInstantiation()
{
    QVBoxLayout *parametersLayout = new QVBoxLayout();
    QVBoxLayout *trainingOutputLayout = new QVBoxLayout();
    DeepLearningWidget *deepLearningWidget = new DeepLearningWidget(parametersLayout, trainingOutputLayout);
    QVERIFY(deepLearningWidget != NULL);
}

void ClassificationTrainingWidgetTests::testRandomForestWidgetInstantiation()
{
    QVBoxLayout *parametersLayout = new QVBoxLayout();
    QVBoxLayout *trainingOutputLayout = new QVBoxLayout();
    RandomForestWidget *randomForestWidget = new RandomForestWidget(parametersLayout, trainingOutputLayout);
    QVERIFY(randomForestWidget != NULL);
}

QTEST_MAIN(ClassificationTrainingWidgetTests)
#include "classification_training_widget_test.moc"
