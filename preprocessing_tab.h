#ifndef DATALOADER_TAB_H
#define DATALOADER_TAB_H

#include "tab.h"
#include "preprocessing_viewer.h"

#include <QFileDialog>

class PreprocessingTab : public Tab
{
    Q_OBJECT
public:
    int maximumRowsOfImages;
    int maximumCollumnsOfImages;

    explicit PreprocessingTab( Tab *parent = nullptr);
    void displayDataBasePreview();
    bool selectDataBasePath();
    void addPreviousNextButtons();
    void addLoadDataBaseButton();

    void handleLoadDataBaseButton();
    void handleLoadPreviousPreviewButton();
    void handleLoadNextPreviewButton();

private:
    QGridLayout *mainLayout;
    ImageCollection *imageCollection;
    PreprocessingViewer *preprocessingViewer;
};
#endif // DATALOADER_TAB_H