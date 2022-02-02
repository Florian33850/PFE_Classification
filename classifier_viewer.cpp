#include "classifier_viewer.h"

#include <iostream>

#include <QFileDialog>
#include <QMenuBar>
#include <QMessageBox>

ClassifierViewer::ClassifierViewer(QWidget *parent)
  : QMainWindow(parent){

  settingMenu(this);
}

ClassifierViewer::~ClassifierViewer() {}

void ClassifierViewer::settingMenu(ClassifierViewer *classifierViewer){
  QMenu *fileMenu = menuBar()->addMenu("&File");
  QAction *openAction = fileMenu->addAction("&Open");
  QAction *helpAction = menuBar()->addAction("&Help");
}
