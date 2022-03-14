#ifndef TAB_H
#define TAB_H

#include "data_handler.h"
#include "image_transformation_viewer.h"
#include "images_preview_widget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#define IMAGES_PREVIEW_MAXIMUM_ROWS 2
#define IMAGES_PREVIEW_MAXIMUM_COLLUMNS 5

class Tab : public QWidget
{
    Q_OBJECT
    public:
        Tab();
        ~Tab();

        DataHandler *dataHandler;
        ImagesPreviewWidget *imagesPreviewWidget;
        std::vector<ImageLabel*> *imagePreviewList;

    protected:
        QGridLayout *mainLayout;
        void clearLayout(QLayout *layout);
};
#endif // TAB_H