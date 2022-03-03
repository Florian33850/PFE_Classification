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
        Tab(QWidget * parent = nullptr);
        ~Tab();

        DataHandler *dataHandler;
        std::vector<ImageLabel*> *imagePreviewList;
    
    protected:
        QGridLayout *mainLayout;
};
#endif // TAB_H