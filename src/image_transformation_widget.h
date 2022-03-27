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

#ifndef IMAGE_TRANSFORMATION_WIDGET_H
#define IMAGE_TRANSFORMATION_WIDGET_H

#include "image_transformation.h"
#include "integer_slider.h"
#include "constants.h"

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QGroupBox>
#include <QGridLayout>

class ImageTransformationWidget : public QWidget
{
    public:
        ImageTransformationWidget(QVBoxLayout *mainLayout, QWidget *parentWidget);

        bool isActivated;
        ImageTransformation *imageTransformation;

        virtual void displayUI(int indexInLayout) = 0;
        void deleteMainWidgetGroupBox();

        QPushButton* getDeleteImageTransformationWidgetButton();
        int getLayoutCount();

    protected:
        QVBoxLayout *mainLayout;
        QWidget *parentWidget;
        QGroupBox *mainWidgetGroupBox;
        QPushButton *deleteImageTransformationWidgetButton;

        void connectWidgetDeleteButton();
};

class MirrorWidget : public ImageTransformationWidget
{
    public:
        MirrorWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, MirrorImageTransformation *mirrorImageTransformation);

        void displayUI(int indexInLayout);

    private:
        QCheckBox *horizontalMirrorCheckBox;
        QCheckBox *verticalMirrorCheckBox;
};

class GrayscaleWidget : public ImageTransformationWidget
{
    public:
        GrayscaleWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, GrayscaleImageTransformation *grayscaleImageTransformation);

        void displayUI(int indexInLayout);
};

class AutomaticRotationLymeDataWidget : public ImageTransformationWidget
{
    public:
        AutomaticRotationLymeDataWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, AutomaticRotationLymeDataImageTransformation *automaticRotationLymeDataImageTransformation);

        void displayUI(int indexInLayout);
};

class MorphologicalTransformationWidget : public ImageTransformationWidget
{
    public:
        MorphologicalTransformationWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, MorphologicalTransformationImageTransformation *morphologicalTransformationImageTransformation);

        void displayUI(int indexInLayout);

    private:
        IntegerSlider *typeMorphologicalTransformation;
        IntegerSlider *kernelSizeSlider;
        IntegerSlider *numberIterationMorphologicalTransformationSlider;
};
#endif // IMAGE_TRANSFORMATION_WIDGET_H
