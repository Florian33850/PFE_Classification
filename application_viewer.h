#ifndef APPLICATION_VIEWER_H
#define APPLICATION_VIEWER_H

#include "classification_training_tab.h"
#include "preprocessing_tab.h"
#include "result_tab.h"

#include <iostream>

#include <QMainWindow>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QMessageBox>

class ApplicationViewer : public QMainWindow {
    Q_OBJECT

public:
    ApplicationViewer(QWidget * parent = 0);
    ~ApplicationViewer();
  
private:
    QVBoxLayout *mainLayout;
    QWidget *mainWidget;
    QTabWidget *tabWidget;

    void settingMenu(ApplicationViewer *applicationViewer);
    void openDataBaseButton(QMenu *menu = NULL);
};
#endif // APPLICATION_VIEWER_H
