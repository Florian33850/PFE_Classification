#include "preprocessing.h"

Mirrored::Mirrored(Preprocessing *parent)
{
    horizontalMirror = false;
    verticalMirror = false;
}

void Mirrored::displayUI(QLayout *layout, QWidget *parentWidget)
{
    QGroupBox *mirrorProcessViewer = new QGroupBox();
    mirrorProcessViewer->setTitle("&Mirror");

    QCheckBox *horizontalMirrorCheckBox = new QCheckBox("Horizontal", parentWidget);
    parentWidget->connect(horizontalMirrorCheckBox, &QCheckBox::toggled, [=](){this->changeHorizontalMirrorMode();});
    QCheckBox *verticalMirrorCheckBox = new QCheckBox("Vertical", parentWidget);
    parentWidget->connect(verticalMirrorCheckBox, &QCheckBox::toggled, [=](){this->changeVerticalMirrorMode();});

    QVBoxLayout *mirrorProcessLayout = new QVBoxLayout();
    mirrorProcessLayout->addWidget(horizontalMirrorCheckBox);
    mirrorProcessLayout->addWidget(verticalMirrorCheckBox);
    mirrorProcessViewer->setLayout(mirrorProcessLayout);

    layout->addWidget(mirrorProcessViewer);
}

void Mirrored::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        QImage mirroredImage = imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().mirrored(horizontalMirror, verticalMirror);
        imageCollection->getImageLabelFromDataBase(imgNumber)->setImage(mirroredImage);
    }
}

void Mirrored::changeHorizontalMirrorMode()
{
    horizontalMirror = !horizontalMirror;
}

void Mirrored::changeVerticalMirrorMode()
{
    verticalMirror = !verticalMirror;
}


Grayscale::Grayscale(Preprocessing *parent)
{

}

void Grayscale::displayUI(QLayout *layout, QWidget *parentWidget)
{
    QGroupBox *grayscaleProcessViewer = new QGroupBox();
    grayscaleProcessViewer->setTitle("&Grayscale");
    layout->addWidget(grayscaleProcessViewer);
}

void Grayscale::runPreprocess(ImageCollection *imageCollection)
{
    for(int imgNumber=0; imgNumber < imageCollection->getDataBaseSize(); imgNumber++)
    {
        QImage grayscaleImage = imageCollection->getImageLabelFromDataBase(imgNumber)->getQImage().convertToFormat(QImage::Format_Grayscale8);
        imageCollection->getImageLabelFromDataBase(imgNumber)->setImage(grayscaleImage);
    }
}