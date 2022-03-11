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

class ApplicationViewer : public QMainWindow
{
    Q_OBJECT
    public:
        ApplicationViewer(QWidget * parent = 0);
        ~ApplicationViewer();
    
    private:
        QVBoxLayout *mainLayout;
        QWidget *mainWidget;
        QTabWidget *tabWidget;
        DataHandler *dataHandler;

        PreprocessingTab *preprocessingTab;
        ClassificationTrainingTab *classificationTrainingTab;
        ResultTab *resultTab;

        void addSettingMenu(ApplicationViewer *applicationViewer);
        void addPreprocessingTab(QTabWidget *mainTabWidget);
        void addClassificationTrainingTab(QTabWidget *mainTabWidget);
        void addResultTab(QTabWidget *mainTabWidget);
        
        void handleOpenImageSelectionDataHandler();
        void handleOpenLymeDatabaseDataHandler();
};
#endif // APPLICATION_VIEWER_H
