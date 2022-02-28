#include "preprocessing_widget.h"

PreprocessingWidget::PreprocessingWidget(QVBoxLayout *mainLayout, QWidget *parentWidget)
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



MirrorWidget::MirrorWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, MirrorPreprocess *mirrorPreprocess)
    : PreprocessingWidget(mainLayout, parentWidget)
{
    this->preprocess = mirrorPreprocess;
    this->horizontalMirrorCheckBox = new QCheckBox("Horizontal", this->parentWidget);
    this->verticalMirrorCheckBox = new QCheckBox("Vertical", this->parentWidget);

    this->mainWidgetGroupBox->setMaximumHeight(MIRRORED_WIDGET_MAXIMUM_HEIGHT);
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

    this->mainWidgetGroupBox->setLayout(mirrorLayout);
    this->mainLayout->insertWidget(this->mainLayout->count()-1, mainWidgetGroupBox);

}



GrayscaleWidget::GrayscaleWidget(QVBoxLayout *mainLayout, QWidget *parentWidget, GrayscalePreprocess *grayscalePreprocessing)
    : PreprocessingWidget(mainLayout, parentWidget)
{
    this->preprocess = grayscalePreprocessing;
    this->mainWidgetGroupBox->setMaximumHeight(GRAYSCALE_WIDGET_MAXIMUM_HEIGHT);
}

void GrayscaleWidget::displayUI()
{
    QLabel *grayscaleWidgetTitle = new QLabel("Grayscale");
    QHBoxLayout *grayscaleLayout = new QHBoxLayout();
    grayscaleLayout->addWidget(grayscaleWidgetTitle);
    grayscaleLayout->addWidget(deletePreprocessingWidgetButton);

    this->mainWidgetGroupBox->setLayout(grayscaleLayout);
    this->mainLayout->insertWidget(this->mainLayout->count()-1, mainWidgetGroupBox);
}