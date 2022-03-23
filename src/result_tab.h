#ifndef RESULT_TAB_H
#define RESULT_TAB_H

#include "tab.h"
#include "image_label.h"
#include "result_thread.h"

#include <QPushButton>
#include <QProcess>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>
#include <QGroupBox>
#include <QFormLayout>
#include <QScrollArea>
#include <QLineEdit>
#include <QFileDialog>

class ResultTab : public Tab
{
    Q_OBJECT
    public:
        ResultTab();

    private:
        QBoxLayout *classificationParametersLayout;
        QBoxLayout *resultOutputLayout;
        QGroupBox *formGroupBox;
        QFormLayout *formLayout;
        QPushButton *addPredicitonFileButton;
        QLineEdit *predictionFileLineEdit;
        QPushButton *addModelClassifierButton;
        QLineEdit *modelClassifierLineEdit;
        QPushButton *addLabelsButton;
        QLineEdit *labelsLineEdit;
        QPushButton *addImageButton;
        QLineEdit *imageLineEdit;
        QPushButton *launchModelButton;

        void readAndDisplayOutputResultFile();

        void addClassificationParametersFormLayout();
        void addLaunchModelButton();

        void handleLaunchModelButton();
        void handleWaitingResult();
        void handleEndingResult();
};
#endif // RESULT_TAB_H
