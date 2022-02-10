#ifndef DATALOADER_TAB_H
#define DATALOADER_TAB_H

#include "tab.h"

class DataloaderTab : public QWidget
{
    Q_OBJECT
public:
    int maxNumberOfImageToDisplay;

    explicit DataloaderTab( QWidget *parent = nullptr);
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