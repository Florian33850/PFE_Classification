#ifndef DataAugmentation_TAB_H
#define DataAugmentation_TAB_H

#include "tab.h"
#include "DataAugmentation_viewer.h"
#include "data_handler.h"

#include <QFileDialog>

class DataAugmentationTab : public Tab
{
    Q_OBJECT
    public:
        DataAugmentationTab( Tab *parent = nullptr);

        DataHandler *dataHandler;
        std::vector<ImageLabel*> *imagePreviewList;
        int maximumRowsOfPreviewImages;
        int maximumCollumnsOfPreviewImages;

        void displayDataBasePreview();

    private:
        QGridLayout *mainLayout;
        QGridLayout *imagesPreviewLayout;
};
#endif // DataAugmentation_TAB_H