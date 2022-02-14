#include "preprocessing_widget.h"

MirroredWidget::MirroredWidget(QLayout *parentLayout, QWidget *parentWidget, Mirrored *mirrored)
{
    this->parentLayout = parentLayout;
    this->parentWidget = parentWidget;
    this->mirrored = mirrored;
    this->mainWidgetGroupBox = new QGroupBox();
    this->horizontalMirrorCheckBox = new QCheckBox("Horizontal", parentWidget);
    this->verticalMirrorCheckBox = new QCheckBox("Vertical", parentWidget);

    mainWidgetGroupBox->setMaximumHeight(100);
}

void MirroredWidget::displayUI()
{
    mainWidgetGroupBox->setTitle("&Mirror");
    parentWidget->connect(horizontalMirrorCheckBox, &QCheckBox::toggled, [=](){this->mirrored->changeHorizontalMirrorMode();});
    parentWidget->connect(verticalMirrorCheckBox, &QCheckBox::toggled, [=](){this->mirrored->changeVerticalMirrorMode();});

    QGridLayout *mirrorLayout = new QGridLayout();
    mirrorLayout->addWidget(horizontalMirrorCheckBox, 0, 0, 1, 1);
    mirrorLayout->addWidget(verticalMirrorCheckBox, 1, 0, 1, 1);
    mainWidgetGroupBox->setLayout(mirrorLayout);

    parentLayout->addWidget(mainWidgetGroupBox);
}




GrayscaleWidget::GrayscaleWidget(QLayout *parentLayout, QWidget *parentWidget, Grayscale *grayscale)
{
    this->parentLayout = parentLayout;
    this->parentWidget = parentWidget;
    this->grayscale = grayscale;
    this->mainWidgetGroupBox = new QGroupBox();

    mainWidgetGroupBox->setMaximumHeight(50);
}

void GrayscaleWidget::displayUI()
{
    mainWidgetGroupBox->setTitle("&Grayscale");

    QHBoxLayout *grayscaleLayout = new QHBoxLayout();
    mainWidgetGroupBox->setLayout(grayscaleLayout);

    parentLayout->addWidget(mainWidgetGroupBox);
}