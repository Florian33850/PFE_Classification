#ifndef RESULT_TAB_H
#define RESULT_TAB_H

#include "tab.h"
#include "model_runner.h"
#include "image_label.h"
#include "result_thread.h"

#include <QPushButton>
#include <QFileDialog>
#include <QProcess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>
#include <QButtonGroup>
#include <QCheckBox>
#include <QGroupBox>

class ResultTab : public Tab
{
    Q_OBJECT
    public:
        ResultTab(Tab *parent = nullptr);

    private:
        QVBoxLayout *mainLayout;
        QCheckBox *modelH5CheckBox;
        QCheckBox *modelPtCheckBox;
        QButtonGroup *modelButtonGroup;
        QVBoxLayout *typeOfModelLayout;
        QGroupBox *modelGroupBox;
        QPushButton *loadModelButton;
        QPushButton *launchModelButton;

        QString pathToModel;
        QString pathToLabels;
        QString pathToImage;
        QString pathToPredictionFile;

        bool isModelLoad;

        void printClassificationResults(ModelRunner model);
        
        void addModelGroupBox();
        void addLoadModelButton();
        void addLaunchModelButton();

        void handleLoadModelButton();
        void handleLaunchModelButton();
        void handleWaitingResult();
        void handleEndingResult();
};
#endif // RESULT_TAB_H
