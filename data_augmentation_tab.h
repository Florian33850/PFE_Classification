#ifndef DATA_AUGMENTATION_TAB_H
#define DATA_AUGMENTATION_TAB_H

#include "tab.h"
#include "data_handler.h"

#include <QPushButton>

class DataAugmentationTab : public Tab
{
    Q_OBJECT
    public:
        DataAugmentationTab( Tab *parent = nullptr);

        DataHandler *dataHandler;
        std::vector<ImageLabel*> *imagePreviewList;
        int maximumRowsOfPreviewImages;
        int maximumCollumnsOfPreviewImages;

        void clearImagesLayout();
        void displayDataBasePreview();
        void addPreviousPreviewButton();
        void addNextPreviewButton();

        void handleLoadDataBase();
        void handleLoadPreviousPreviewButton();
        void handleLoadNextPreviewButton();

    private:
        QGridLayout *mainLayout;
        QGridLayout *imagesLayout;
};
#endif // DATA_AUGMENTATION_TAB_H