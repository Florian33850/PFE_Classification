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
    mirrorLayout->addWidget(mirrorWidgetTitle, 0, 0, 1, 1);
    mirrorLayout->addWidget(horizontalMirrorCheckBox, 1, 0, 2, 1);
    mirrorLayout->addWidget(verticalMirrorCheckBox, 2, 0, 2, 1);
    mirrorLayout->addWidget(deleteImageTransformationWidgetButton, 0, 1, 1, 1);

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
    this->kernelSizeSlider = new IntegerSlider("Kernel Size", 0, 20);
    this->numberIterationMorphologialTransformationSlider = new IntegerSlider("Number of Iteration", 1, 20);

    this->mainWidgetGroupBox->adjustSize();
}

void MorphologicalTransformationWidget::displayUI(int indexInLayout)
{
    parentWidget->connect(this->typeMorphologicalTransformation, &IntegerSlider::valueChanged, [=](){static_cast<MorphologicalTransformationImageTransformation*>(this->imageTransformation)->changeTypeMorphologicalTransformation(this->typeMorphologicalTransformation->value());});
    parentWidget->connect(this->kernelSizeSlider, &IntegerSlider::valueChanged, [=](){static_cast<MorphologicalTransformationImageTransformation*>(this->imageTransformation)->changeKernelSize(this->kernelSizeSlider->value());});
    parentWidget->connect(this->numberIterationMorphologialTransformationSlider, &IntegerSlider::valueChanged, [=](){static_cast<MorphologicalTransformationImageTransformation*>(this->imageTransformation)->changeNumberIterationMorphologicalTransformation(this->numberIterationMorphologialTransformationSlider->value());});

    QGridLayout *morphologicalTransformationLayout = new QGridLayout();
    QLabel *morphologicalTransformationWidgetTitle = new QLabel("Morphological Transformation");
    morphologicalTransformationLayout->addWidget(morphologicalTransformationWidgetTitle, 0, 0, Qt::AlignLeft);
    morphologicalTransformationLayout->addWidget(this->typeMorphologicalTransformation, 1, 0, Qt::AlignLeft);
    morphologicalTransformationLayout->addWidget(this->kernelSizeSlider, 2, 0, Qt::AlignLeft);
    morphologicalTransformationLayout->addWidget(this->numberIterationMorphologialTransformationSlider, 3, 0, Qt::AlignLeft);
    morphologicalTransformationLayout->addWidget(deleteImageTransformationWidgetButton, 0, 1, Qt::AlignRight);

    this->mainWidgetGroupBox->setLayout(morphologicalTransformationLayout);
    this->mainLayout->insertWidget(indexInLayout, mainWidgetGroupBox);
}