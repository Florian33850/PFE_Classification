#ifndef CLASSIFICATION_TRAINING_TAB_H
#define CLASSIFICATION_TRAINING_TAB_H

#include "tab.h"
#include "model_runner.h"
#include "image_label.h"

#include <QLabel>
#include <QFileDialog>
#include <QPushButton>


class ClassificationTrainingTab : public Tab
{
    Q_OBJECT

public:
    explicit ClassificationTrainingTab(Tab *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QString pathToModel;
    QString pathToLabels;
    QString pathToImage;
    bool modelLoad = false;

    void handleLoadModelButton();
    void handleLaunchModelButton();

    void printClassificationResults(ModelRunner model);
};
#endif // CLASSIFICATION_TRAINING_TAB_H