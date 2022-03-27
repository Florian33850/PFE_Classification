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

#include "../src/image_transformation_widget.h"

class ImageTransformationWidgetTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testMirrorWidgetInstantiation();
        void testGrayscaleWidgetInstantiation();
        void testAutomaticRotationLymeDataWidgetInstantiation();
        void testMorphologicalTransformationWidgetInstantiation();
};

void ImageTransformationWidgetTests::testMirrorWidgetInstantiation()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *parentWidget = new QWidget();
    MirrorImageTransformation *mirrorImageTransformation = new MirrorImageTransformation();
    MirrorWidget *mirrorWidget = new MirrorWidget(mainLayout, parentWidget, mirrorImageTransformation);
    QVERIFY(mirrorWidget != NULL);
}

void ImageTransformationWidgetTests::testGrayscaleWidgetInstantiation()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *parentWidget = new QWidget();
    GrayscaleImageTransformation *grayscaleImageTransformation = new GrayscaleImageTransformation();
    GrayscaleWidget *grayscaleWidget = new GrayscaleWidget(mainLayout, parentWidget, grayscaleImageTransformation);
    QVERIFY(grayscaleWidget != NULL);
}

void ImageTransformationWidgetTests::testAutomaticRotationLymeDataWidgetInstantiation()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *parentWidget = new QWidget();
    AutomaticRotationLymeDataImageTransformation *automaticRotationImageTransformation = new AutomaticRotationLymeDataImageTransformation();
    AutomaticRotationLymeDataWidget *automaticRotationWidget = new AutomaticRotationLymeDataWidget(mainLayout, parentWidget, automaticRotationImageTransformation);
    QVERIFY(automaticRotationWidget != NULL);
}

void ImageTransformationWidgetTests::testMorphologicalTransformationWidgetInstantiation()
{
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QWidget *parentWidget = new QWidget();
    MorphologicalTransformationImageTransformation *morphologicalTransformationImageTransformation = new MorphologicalTransformationImageTransformation();
    MorphologicalTransformationWidget *morphologicalTransformationWidget = new MorphologicalTransformationWidget(mainLayout, parentWidget, morphologicalTransformationImageTransformation);
    QVERIFY(morphologicalTransformationWidget != NULL);
}

QTEST_MAIN(ImageTransformationWidgetTests)
#include "image_transformation_widget_test.moc"
