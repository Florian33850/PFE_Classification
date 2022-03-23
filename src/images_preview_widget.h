#ifndef IMAGES_PREVIEW_WIDGET_H
#define IMAGES_PREVIEW_WIDGET_H

#include "data_handler.h"
#include "image_transformation_viewer.h"
#include "constants.h"
#include "utils.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

class ImagesPreviewWidget : public QWidget
{
    Q_OBJECT
    public:
        ImagesPreviewWidget(std::vector<ImageLabel*> *imagePreviewList, ImageTransformationViewer *imageTransformationViewer = nullptr);

        DataHandler *dataHandler;
        std::vector<ImageLabel*> *imagePreviewList;

        void display(DataHandler *dataHandler);
        void reloadPreview();

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