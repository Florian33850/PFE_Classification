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
    return deleteImageTransformationWidgetButton;
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

    this->mainWidgetGroupBox->setMaximumHeight(MIRRORED_WIDGET_MAXIMUM_HEIGHT);
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
    this->mainWidgetGroupBox->setMaximumHeight(GRAYSCALE_WIDGET_MAXIMUM_HEIGHT);
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
    this->mainWidgetGroupBox->setMaximumHeight(AUTOMATIC_ROTATION_WIDGET_MAXIMUM_HEIGHT);
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



ErosionWidget::ErosionWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, ErosionImageTransformation *erosionImageTransformation)
    : ImageTransformationWidget(mainLayout, parentWidget)
{
    this->imageTransformation = erosionImageTransformation;
    this->kernelSizeSlider = new IntegerSlider("Kernel Size", 0, 20);
    this->numberIterationErosionSlider = new IntegerSlider("Number of Iteration", 1, 20);

    this->mainWidgetGroupBox->setMaximumHeight(EROSION_WIDGET_MAXIMUM_HEIGHT);
}

void ErosionWidget::displayUI(int indexInLayout)
{
    parentWidget->connect(this->kernelSizeSlider, &IntegerSlider::valueChanged, [=]()
        {static_cast<ErosionImageTransformation*>(this->imageTransformation)->changeKernelSize(this->kernelSizeSlider->value());});

    parentWidget->connect(this->numberIterationErosionSlider, &IntegerSlider::valueChanged, [=]()
        {static_cast<ErosionImageTransformation*>(this->imageTransformation)->changeNumberIterationErosion(this->numberIterationErosionSlider->value());});

    QGridLayout *erosionLayout = new QGridLayout();
    QLabel *erosionWidgetTitle = new QLabel("Erosion");
    erosionLayout->addWidget(erosionWidgetTitle, 0, 0, Qt::AlignLeft);
    erosionLayout->addWidget(this->kernelSizeSlider, 1, 0, Qt::AlignLeft);
    erosionLayout->addWidget(this->numberIterationErosionSlider, 2, 0, Qt::AlignLeft);
    erosionLayout->addWidget(deleteImageTransformationWidgetButton, 0, 1, Qt::AlignRight);

    this->mainWidgetGroupBox->setLayout(erosionLayout);
    this->mainLayout->insertWidget(indexInLayout, mainWidgetGroupBox);
}