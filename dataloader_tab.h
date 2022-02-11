#ifndef DATALOADER_TAB_H
#define DATALOADER_TAB_H

#include "tab.h"
#include "preprocessing_viewer.h"

class DataloaderTab : public Tab
{
    Q_OBJECT
public:
    int maxNumberOfImagesToDisplay;

    explicit DataloaderTab( Tab *parent = nullptr);
    void displayDataBaseImages();
    bool selectDataBasePath();

public Q_SLOTS:
    void handleLoadDataBaseButton();

private:
    ImageCollection *imgCollection;
    QVBoxLayout *mainLayout;

    void updateWindow();
};
#endif // DATALOADER_TAB_H