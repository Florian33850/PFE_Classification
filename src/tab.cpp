#include "tab.h"

#include <iostream>

Tab::Tab()
{
    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(1);
    this->mainLayout->setMargin(1);
    this->setLayout(this->mainLayout);
}

Tab::~Tab() {}

void Tab::clearLayout(QLayout *layout)
{
    QLayoutItem *itemLayout;

    int firstImagePosition = 0;
    QLayoutItem *empty = 0;

    while ((itemLayout = layout->takeAt(firstImagePosition)) != empty)
    {
        layout->removeItem(itemLayout);
        delete itemLayout->widget();
        delete itemLayout;
    }
}

void Tab::handleSaveButton(QString pathToSave)
{
    QMessageBox saveStartMessage;
    saveStartMessage.setWindowTitle("Information");
    saveStartMessage.setText("Data Base is saving...");
    saveStartMessage.exec();

    if(this->dataHandler->saveImagesInFile(this->imageTransformationViewer->getImageTransformationWidgetList(), pathToSave))
    {
        QMessageBox saveEndMessage;
        saveEndMessage.setWindowTitle("Information");
        saveEndMessage.setText("Data Base correctly saved.");
        saveEndMessage.exec();
    }
}
