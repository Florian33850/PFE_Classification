#ifndef TAB_H
#define TAB_H

#include "data_handler.h"
#include "image_transformation_viewer.h"
#include "images_preview_widget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>

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
        ImageTransformationViewer *imageTransformationViewer;

        void clearLayout(QLayout *layout);

        void handleSaveButton(QString pathToSave);
        void handleStartSave(QString pathToSave);
        void handleEndSave();
};
#endif // TAB_H