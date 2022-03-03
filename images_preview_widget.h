#ifndef IMAGES_PREVIEW_WIDGET_H
#define IMAGES_PREVIEW_WIDGET_H

#include "data_handler.h"
#include "image_transformation_viewer.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#define IMAGES_PREVIEW_MAXIMUM_ROWS 2
#define IMAGES_PREVIEW_MAXIMUM_COLLUMNS 5

class ImagesPreviewWidget : public QWidget
{
    Q_OBJECT
    public:
        ImagesPreviewWidget(std::vector<ImageLabel*> *imagePreviewList, ImageTransformationViewer *imageTransformationViewer = nullptr);

        DataHandler *dataHandler;
        std::vector<ImageLabel*> *imagePreviewList;

        void clearImagesLayout();

        void display(DataHandler *dataHandler);

    private:
        QGridLayout *mainLayout;
        QGridLayout *imagesLayout;
        ImageTransformationViewer *imageTransformationViewer;

        void displayDataBasePreview();
        void addPreviousPreviewButton();
        void addNextPreviewButton();

        void handleLoadPreviousPreviewButton();
        void handleLoadNextPreviewButton();

};
#endif // IMAGES_PREVIEW_WIDGET_H