#include "tab.h"

#include <iostream>

Tab::Tab(QWidget *parent) : QWidget(parent){
    this->mainLayout = new QGridLayout();
    this->mainLayout->setSpacing(1);
    this->mainLayout->setMargin(1);
    
    this->setLayout(this->mainLayout);
}

Tab::~Tab() {}