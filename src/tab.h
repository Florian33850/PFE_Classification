#ifndef TAB_H
#define TAB_H

#include "images_preview_widget.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QCoreApplication>
#include <QTextCodec>
#include <QtCore>

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

        void handleSaveButton(QString pathToSave);
        void handleStartSave(QString pathToSave);
        void handleEndSave();
};
#endif // TAB_H