#ifndef DATA_AUGMENTATION_TAB_H
#define DATA_AUGMENTATION_TAB_H

#include "tab.h"

class DataAugmentationTab : public Tab
{
    Q_OBJECT
    public:
        DataAugmentationTab( Tab *parent = nullptr);
        std::vector<ImageLabel*> *imagePreviewList;
        ImagesPreviewWidget *imagesPreviewWidget;

    private:
        ImageTransformationViewer *imageTransformationViewer;
};
#endif // DATA_AUGMENTATION_TAB_H