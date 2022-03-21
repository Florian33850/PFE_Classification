#ifndef PREPROCESSING_TAB_H
#define PREPROCESSING_TAB_H

#include "tab.h"
#include "image_transformation_viewer.h"
#include "data_handler.h"

#include <QFileDialog>

class PreprocessingTab : public Tab
{
    Q_OBJECT
    public:
        PreprocessingTab();

        void addSaveButton();
        void handleNewDataHandler(DataHandler *dataHandler);
};
#endif // PREPROCESSING_TAB_H