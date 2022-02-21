#ifndef DATALOADER_TAB_H
#define DATALOADER_TAB_H

#include "tab.h"
#include "preprocessing_viewer.h"

#include <QFileDialog>

class DataloaderTab : public Tab
{
    Q_OBJECT
public:
    int maximumRowsOfImages;
    int maximumCollumnsOfImages;

    explicit DataloaderTab( Tab *parent = nullptr);
    void displayDataBasePreview();
    bool selectDataBasePath();
    void addPreviousNextButtons();

    void handleLoadDataBaseButton();
    void handleLoadPreviousPreviewButton();
    void handleLoadNextPreviewButton();

private:
    ImageCollection *imageCollection;
    QGridLayout *mainLayout;
};
#endif // DATALOADER_TAB_H