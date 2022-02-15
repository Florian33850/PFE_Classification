#include "preprocessing_widget.h"

QPushButton* PreprocessingWidget::getDeletePreprocessingWidgetButton()
{
    return deletePreprocessingWidgetButton;
}

void PreprocessingWidget::deleteMainWidgetGroupBox()
{
    delete this->mainWidgetGroupBox;
}

// QLabel PreprocessingWidget::createTextLabel(QString titleName)
// {
//     QLabel title = new QL
// }

MirroredWidget::MirroredWidget(QLayout *parentLayout, QWidget *parentWidget, Mirrored *mirrored)
{
    this->parentLayout = parentLayout;
    this->parentWidget = parentWidget;
    this->mirrored = mirrored;
    this->quuid = new QUuid();
    this->mainWidgetGroupBox = new QGroupBox();
    this->deletePreprocessingWidgetButton = new QPushButton("x");
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
    mirrorLayout->addWidget(deletePreprocessingWidgetButton, 0, 1, 1, 1);
    mainWidgetGroupBox->setLayout(mirrorLayout);

    parentLayout->addWidget(mainWidgetGroupBox);
}




GrayscaleWidget::GrayscaleWidget(QLayout *parentLayout, QWidget *parentWidget, Grayscale *grayscale)
{
    this->parentLayout = parentLayout;
    this->parentWidget = parentWidget;
    this->grayscale = grayscale;
    this->quuid = new QUuid();
    this->mainWidgetGroupBox = new QGroupBox();
    this->deletePreprocessingWidgetButton = new QPushButton("x");

    mainWidgetGroupBox->setMaximumHeight(65);
}

void GrayscaleWidget::displayUI()
{
    QLabel *grayscaleWidgetTitle = new QLabel("Grayscale");
    QHBoxLayout *grayscaleLayout = new QHBoxLayout();
    mainWidgetGroupBox->setLayout(grayscaleLayout);
    grayscaleLayout->addWidget(grayscaleWidgetTitle);
    grayscaleLayout->addWidget(deletePreprocessingWidgetButton);

    parentLayout->addWidget(mainWidgetGroupBox);
}