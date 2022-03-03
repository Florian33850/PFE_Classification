#include "tab.h"

#include <iostream>

Tab::Tab(QWidget *parent)
  : QWidget(parent){
}

Tab::~Tab() {}

void Tab::handleAddDirectoryToQlineEdit(QLineEdit *qLineEdit)
{
    qLineEdit->setText(QFileDialog::getExistingDirectory(this));
}

void Tab::handleAddFileToQlineEdit(QLineEdit *qLineEdit)
{
    qLineEdit->setText(QFileDialog::getOpenFileName(this));
}
