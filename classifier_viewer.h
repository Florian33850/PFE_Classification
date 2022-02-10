#ifndef CLASSIFIER_VIEWER_H
#define CLASSIFIER_VIEWER_H

#include "classification_training_tab.h"
#include "dataloader_tab.h"
#include "result_tab.h"

#include <iostream>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMessageBox>

class ClassifierViewer : public QMainWindow {
    Q_OBJECT

public:
    ClassifierViewer(QWidget * parent = 0);
    ~ClassifierViewer();
  
private:
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;
    QTabWidget *tabWidget;

    void settingMenu(ClassifierViewer *classifierViewer);
    void openDataBaseButton(QMenu *menu = NULL);
};
#endif // CLASSIFIER_VIEWER_H
