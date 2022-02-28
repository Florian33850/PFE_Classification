#ifndef PREPROCESSING_TAB_H
#define PREPROCESSING_TAB_H

#include "tab.h"
#include "preprocessing_viewer.h"
#include "data_loader.h"

#include <QFileDialog>

class PreprocessingTab : public Tab
{
    Q_OBJECT
    public:
        PreprocessingTab( Tab *parent = nullptr);

        DataLoader *dataLoader;
        ImageCollection *imageCollection;
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
        PreprocessingViewer *preprocessingViewer;
};
#endif // PREPROCESSING_TAB_H