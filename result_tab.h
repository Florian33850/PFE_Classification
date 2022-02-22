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
    explicit ResultTab(Tab *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QVBoxLayout *typeOfModelLayout;

    QString pathToModel;
    QString pathToLabels;
    QString pathToImage;
    QString pathToPredictionFile;

    bool isModelLoad;

    QPushButton *loadModelButton;
    QCheckBox *modelH5CheckBox;
    QCheckBox *modelPtCheckBox;
    QButtonGroup *buttonGroup;
    QPushButton *launchModelButton;

    void handleLoadModelButton();
    void handleLaunchModelButton();

    void printClassificationResults(ModelRunner model);
    void handleWaitingResult();
    void handleEndingResult();
};
#endif // RESULT_TAB_H