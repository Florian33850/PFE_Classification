#ifndef DATA_AUGMENTATION_TAB_H
#define DATA_AUGMENTATION_TAB_H

#include "tab.h"

class DataAugmentationTab : public Tab
{
    Q_OBJECT
    public:
        DataAugmentationTab();

        void handleNewDataHandler(DataHandler *dataHandler);

    private:
        ImageTransformationViewer *imageTransformationViewer;

        QVBoxLayout *dataBaseCountLayout;

        void addDataBaseCountDisplay();
};
#endif // DATA_AUGMENTATION_TAB_H