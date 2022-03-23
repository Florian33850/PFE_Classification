#ifndef DATA_AUGMENTATION_TAB_H
#define DATA_AUGMENTATION_TAB_H

#include "tab.h"

#define ROW_IMAGES_PREVIEW_WIDGET 0
#define COLUMN_IMAGES_PREVIEW_WIDGET 0
#define ROW_SPAN_IMAGES_PREVIEW_WIDGET 3
#define COLUMN_SPAN_IMAGES_PREVIEW_WIDGET 3

#define ROW_TRANSFORMATION_VIEWER 0
#define COLUMN_TRANSFORMATION_VIEWER 3
#define ROW_SPAN_TRANSFORMATION_VIEWER 3
#define COLUMN_SPAN_TRANSFORMATION_VIEWER 1

#define ROW_SAVE_IMAGES_BUTTON 3
#define COLUMN_SAVE_IMAGES_BUTTON 3
#define ROW_SPAN_SAVE_IMAGES_BUTTON 1
#define COLUMN_SPAN_SAVE_IMAGES_BUTTON 1

#define ROW_DATABASE_COUNT_LAYOUT 3
#define COLUMN_DATABASE_COUNT_LAYOUT 0
#define ROW_SPAN_DATABASE_COUNT_LAYOUT 1
#define COLUMN_SPAN_DATABASE_COUNT_LAYOUT 3

class DataAugmentationTab : public Tab
{
    Q_OBJECT
    public:
        DataAugmentationTab();

        void handleNewDataHandler(DataHandler *dataHandler);

    private:
        QVBoxLayout *dataBaseCountLayout;
        QLabel *originalImagesLabel;

        void addDataBaseCountDisplay();
        void refreshDataBaseCountDisplay();
        void addSaveButton();
};
#endif // DATA_AUGMENTATION_TAB_H