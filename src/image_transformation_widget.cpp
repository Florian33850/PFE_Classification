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

#include "image_transformation_widget.h"

ImageTransformationWidget::ImageTransformationWidget(QVBoxLayout *mainLayout, QWidget *parentWidget)
{
    this->mainLayout = mainLayout;
    this->parentWidget = parentWidget;
    this->mainWidgetGroupBox = new QGroupBox();
    this->deleteImageTransformationWidgetButton = new QPushButton("x");
    this->isActivated = false;
}

void ImageTransformationWidget::deleteMainWidgetGroupBox()
{
    delete this->mainWidgetGroupBox;
}

QPushButton* ImageTransformationWidget::getDeleteImageTransformationWidgetButton()
{
    return this->deleteImageTransformationWidgetButton;
}

int ImageTransformationWidget::getLayoutCount()
{
    return this->mainLayout->count();
}

MirrorWidget::MirrorWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, MirrorImageTransformation *mirrorImageTransformation)
    : ImageTransformationWidget(mainLayout, parentWidget)
{
    this->imageTransformation = mirrorImageTransformation;
    this->horizontalMirrorCheckBox = new QCheckBox("Horizontal", this->parentWidget);
    this->verticalMirrorCheckBox = new QCheckBox("Vertical", this->parentWidget);

    this->mainWidgetGroupBox->adjustSize();
}

void MirrorWidget::displayUI(int indexInLayout)
{
    parentWidget->connect(horizontalMirrorCheckBox, &QCheckBox::toggled, [=](){static_cast<MirrorImageTransformation*>(this->imageTransformation)->changeHorizontalMirrorMode();});
    parentWidget->connect(verticalMirrorCheckBox, &QCheckBox::toggled, [=](){static_cast<MirrorImageTransformation*>(this->imageTransformation)->changeVerticalMirrorMode();});

    QGridLayout *mirrorLayout = new QGridLayout();
    QLabel *mirrorWidgetTitle = new QLabel("Mirror");
    mirrorLayout->addWidget(mirrorWidgetTitle, ROW_MIRROR_WIDGET_TITLE, COLUMN_MIRROR_WIDGET_TITLE,
                                                ROW_SPAN_MIRROR_WIDGET_TITLE, COLUMN_SPAN_MIRROR_WIDGET_TITLE);
    mirrorLayout->addWidget(horizontalMirrorCheckBox, ROW_HORIZONTAL_CHECK_BOX, COLUMN_HORIZONTAL_CHECK_BOX,
                                                        ROW_SPAN_HORIZONTAL_CHECK_BOX, COLUMN_SPAN_HORIZONTAL_CHECK_BOX);
    mirrorLayout->addWidget(verticalMirrorCheckBox, ROW_VERTICAL_CHECK_BOX, COLUMN_VERTICAL_CHECK_BOX,
                                                    ROW_SPAN_VERTICAL_CHECK_BOX, COLUMN_SPAN_VERTICAL_CHECK_BOX);
    mirrorLayout->addWidget(deleteImageTransformationWidgetButton, ROW_DELETE_WIDGET_BUTTON, COLUMN_DELETE_WIDGET_BUTTON,
                                                                    ROW_SPAN_DELETE_WIDGET_BUTTON, COLUMN_SPAN_DELETE_WIDGET_BUTTON);

    this->mainWidgetGroupBox->setLayout(mirrorLayout);
    this->mainLayout->insertWidget(indexInLayout, mainWidgetGroupBox);
}

GrayscaleWidget::GrayscaleWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, GrayscaleImageTransformation *grayscaleImageTransformation)
    : ImageTransformationWidget(mainLayout, parentWidget)
{
    this->imageTransformation = grayscaleImageTransformation;
    this->mainWidgetGroupBox->adjustSize();
}

void GrayscaleWidget::displayUI(int indexInLayout)
{
    QLabel *grayscaleWidgetTitle = new QLabel("Grayscale");
    QHBoxLayout *grayscaleLayout = new QHBoxLayout();
    grayscaleLayout->addWidget(grayscaleWidgetTitle);
    grayscaleLayout->addWidget(deleteImageTransformationWidgetButton);

    this->mainWidgetGroupBox->setLayout(grayscaleLayout);
    this->mainLayout->insertWidget(indexInLayout, mainWidgetGroupBox);
}

AutomaticRotationLymeDataWidget::AutomaticRotationLymeDataWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, AutomaticRotationLymeDataImageTransformation *automaticRotationLymeDataImageTransformation)
    : ImageTransformationWidget(mainLayout, parentWidget)
{
    this->imageTransformation = automaticRotationLymeDataImageTransformation;
    this->mainWidgetGroupBox->adjustSize();
}

void AutomaticRotationLymeDataWidget::displayUI(int indexInLayout)
{
    QLabel *automaticRotationLymeDataWidgetTitle = new QLabel("Automatic Rotation");
    QHBoxLayout *automaticRotationLymeDataLayout = new QHBoxLayout();
    automaticRotationLymeDataLayout->addWidget(automaticRotationLymeDataWidgetTitle);
    automaticRotationLymeDataLayout->addWidget(deleteImageTransformationWidgetButton);

    this->mainWidgetGroupBox->setLayout(automaticRotationLymeDataLayout);
    this->mainLayout->insertWidget(indexInLayout, mainWidgetGroupBox);
}

MorphologicalTransformationWidget::MorphologicalTransformationWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, MorphologicalTransformationImageTransformation *morphologicalTransformationImageTransformation)
    : ImageTransformationWidget(mainLayout, parentWidget)
{
    this->imageTransformation = morphologicalTransformationImageTransformation;
    this->typeMorphologicalTransformation = new IntegerSlider("Erosion(0), Dilatation(1)", 0, 1);
    this->kernelSizeSlider = new IntegerSlider("Kernel Size", MORPHOLOGICAL_TRANSFORMATION_MINIMUM_KERNEL_SIZE, MORPHOLOGICAL_TRANSFORMATION_MAXIMUM_KERNEL_SIZE);
    this->numberIterationMorphologicalTransformationSlider = new IntegerSlider("Number of Iteration", MORPHOLOGICAL_TRANSFORMATION_MINIMUM_NUMBER_ITERATION, MORPHOLOGICAL_TRANSFORMATION_MAXIMUM_NUMBER_ITERATION);

    this->mainWidgetGroupBox->adjustSize();
}

void MorphologicalTransformationWidget::displayUI(int indexInLayout)
{
    parentWidget->connect(this->typeMorphologicalTransformation, &IntegerSlider::valueChanged, [=](){static_cast<MorphologicalTransformationImageTransformation*>(this->imageTransformation)->changeTypeMorphologicalTransformation(this->typeMorphologicalTransformation->value());});
    parentWidget->connect(this->kernelSizeSlider, &IntegerSlider::valueChanged, [=](){static_cast<MorphologicalTransformationImageTransformation*>(this->imageTransformation)->changeKernelSize(this->kernelSizeSlider->value());});
    parentWidget->connect(this->numberIterationMorphologicalTransformationSlider, &IntegerSlider::valueChanged, [=](){static_cast<MorphologicalTransformationImageTransformation*>(this->imageTransformation)->changeNumberIterationMorphologicalTransformation(this->numberIterationMorphologicalTransformationSlider->value());});

    QGridLayout *morphologicalTransformationLayout = new QGridLayout();
    QLabel *morphologicalTransformationWidgetTitle = new QLabel("Morphological Transformation");
    morphologicalTransformationLayout->addWidget(morphologicalTransformationWidgetTitle, ROW_MORPHOLOGICAL_TRANSFORMATION_WIDGET_TITLE, COLUMN_MORPHOLOGICAL_TRANSFORMATION_WIDGET_TITLE, Qt::AlignLeft);
    morphologicalTransformationLayout->addWidget(this->typeMorphologicalTransformation, ROW_MORPHOLOGICAL_TRANSFORMATION_TYPE, COLUMN_MORPHOLOGICAL_TRANSFORMATION_TYPE, Qt::AlignLeft);
    morphologicalTransformationLayout->addWidget(this->kernelSizeSlider, ROW_MORPHOLOGICAL_TRANSFORMATION_KERNEL_SIZE_SLIDER, COLUMN_MORPHOLOGICAL_TRANSFORMATION_KERNEL_SIZE_SLIDER, Qt::AlignLeft);
    morphologicalTransformationLayout->addWidget(this->numberIterationMorphologicalTransformationSlider, ROW_MORPHOLOGICAL_TRANSFORMATION_NUMBER_ITERATION, COLUMN_MORPHOLOGICAL_TRANSFORMATION_NUMBER_ITERATION, Qt::AlignLeft);
    morphologicalTransformationLayout->addWidget(this->deleteImageTransformationWidgetButton, ROW_MORPHOLOGICAL_TRANSFORMATION_DELETE_WIDGET_BUTTON, COLUMN_MORPHOLOGICAL_TRANSFORMATION_DELETE_WIDGET_BUTTON, Qt::AlignRight);

    this->mainWidgetGroupBox->setLayout(morphologicalTransformationLayout);
    this->mainLayout->insertWidget(indexInLayout, mainWidgetGroupBox);
}
