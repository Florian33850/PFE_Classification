#ifndef RESULT_TAB_H
#define RESULT_TAB_H

#include "tab.h"
#include "model_runner.h"
#include "image_label.h"

#include <QPushButton>
#include <QFileDialog>

class ResultTab : public Tab
{
    Q_OBJECT

public:
    explicit ResultTab(Tab *parent = nullptr);

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
#endif // RESULT_TAB_H
