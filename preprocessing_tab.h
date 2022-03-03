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
        PreprocessingTab( Tab *parent = nullptr);

        std::vector<ImageLabel*> *imagesPreviewList;
        ImagesPreviewWidget *imagesPreviewWidget;

    private:
        ImageTransformationViewer *imageTransformationViewer;
};
#endif // PREPROCESSING_TAB_H