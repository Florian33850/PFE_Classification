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
