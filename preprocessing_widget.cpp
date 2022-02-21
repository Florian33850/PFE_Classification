#include "preprocessing_widget.h"

PreprocessingWidget::PreprocessingWidget(QLayout *mainLayout, QWidget *parentWidget)
{
    this->mainLayout = mainLayout;
    this->parentWidget = parentWidget;
    this->mainWidgetGroupBox = new QGroupBox();
    this->deletePreprocessingWidgetButton = new QPushButton("x");
    this->isActivated = false;
}

void PreprocessingWidget::deleteMainWidgetGroupBox()
{
    delete this->mainWidgetGroupBox;
}

QPushButton* PreprocessingWidget::getDeletePreprocessingWidgetButton()
{
    return deletePreprocessingWidgetButton;
}


MirrorWidget::MirrorWidget(QLayout *mainLayout, QWidget *parentWidget, MirrorPreprocess *mirrorPreprocess)
 : PreprocessingWidget(mainLayout, parentWidget)
{
    this->preprocess = mirrorPreprocess;
    this->horizontalMirrorCheckBox = new QCheckBox("Horizontal", parentWidget);
    this->verticalMirrorCheckBox = new QCheckBox("Vertical", parentWidget);

    mainWidgetGroupBox->setMaximumHeight(MIRRORED_WIDGET_MAXIMUM_HEIGHT);
}

void MirrorWidget::displayUI()
{
    parentWidget->connect(horizontalMirrorCheckBox, &QCheckBox::toggled, [=](){static_cast<MirrorPreprocess*>(this->preprocess)->changeHorizontalMirrorMode();});
    parentWidget->connect(verticalMirrorCheckBox, &QCheckBox::toggled, [=](){static_cast<MirrorPreprocess*>(this->preprocess)->changeVerticalMirrorMode();});

    QGridLayout *mirrorLayout = new QGridLayout();
    QLabel *mirrorWidgetTitle = new QLabel("Mirror");
    mirrorLayout->addWidget(mirrorWidgetTitle, 0, 0, 1, 1);
    mirrorLayout->addWidget(horizontalMirrorCheckBox, 1, 0, 2, 1);
    mirrorLayout->addWidget(verticalMirrorCheckBox, 2, 0, 2, 1);
    mirrorLayout->addWidget(deletePreprocessingWidgetButton, 0, 1, 1, 1);

    mainWidgetGroupBox->setLayout(mirrorLayout);
    mainLayout->addWidget(mainWidgetGroupBox);
}



GrayscaleWidget::GrayscaleWidget(QLayout *mainLayout, QWidget *parentWidget, GrayscalePreprocess *grayscalePreprocessing)
 : PreprocessingWidget(mainLayout, parentWidget)
{
    this->preprocess = grayscalePreprocessing;

    mainWidgetGroupBox->setMaximumHeight(GRAYSCALE_WIDGET_MAXIMUM_HEIGHT);
}

void GrayscaleWidget::displayUI()
{
    QLabel *grayscaleWidgetTitle = new QLabel("Grayscale");
    QHBoxLayout *grayscaleLayout = new QHBoxLayout();
    mainWidgetGroupBox->setLayout(grayscaleLayout);
    grayscaleLayout->addWidget(grayscaleWidgetTitle);
    grayscaleLayout->addWidget(deletePreprocessingWidgetButton);

    mainLayout->addWidget(mainWidgetGroupBox);
}