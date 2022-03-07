#include "tab.h"

#include <iostream>

Tab::Tab(QWidget *parent)
  : QWidget(parent){
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
