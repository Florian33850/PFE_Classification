#ifndef DATALOADER_TAB_H
#define DATALOADER_TAB_H

#include "tab.h"
#include "preprocessing_viewer.h"

class DataloaderTab : public Tab
{
    Q_OBJECT
public:
    int maximumNumberOfImagesToDisplay;
    int maximumRowsOfImages;
    int maximumCollumnsOfImages;

    explicit DataloaderTab( Tab *parent = nullptr);
    void displayDataBaseImages();
    bool selectDataBasePath();

public Q_SLOTS:
    void handleLoadDataBaseButton();

private:
    ImageCollection *imageCollection;
    QGridLayout *mainLayout;

    void updateWindow();
};
#endif // DATALOADER_TAB_H