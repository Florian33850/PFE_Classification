#ifndef PREPROCESSING_TAB_H
#define PREPROCESSING_TAB_H

#include "tab.h"
#include "preprocessing_viewer.h"
#include "data_handler.h"

#include <QFileDialog>

class PreprocessingTab : public Tab
{
    Q_OBJECT
    public:
        PreprocessingTab( Tab *parent = nullptr);

        DataHandler *dataHandler;
        std::vector<ImageLabel*> *imagePreviewList;
        int maximumRowsOfPreviewImages;
        int maximumCollumnsOfPreviewImages;

        void displayDataBasePreview();
        void addPreviousPreviewButton();
        void addNextPreviewButton();

        void handleLoadDataBase();
        void handleLoadPreviousPreviewButton();
        void handleLoadNextPreviewButton();

    private:
        QGridLayout *mainLayout;
        QGridLayout *imagesPreviewLayout;
        PreprocessingViewer *preprocessingViewer;
};
#endif // PREPROCESSING_TAB_H