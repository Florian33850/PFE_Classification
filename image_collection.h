#ifndef IMAGE_COLLECTION_H
#define IMAGE_COLLECTION_H

#include <image_label.h>

#include <QMainWindow>
#include <QVBoxLayout>


class ImageCollection {

  public:
    ImageCollection();

    void loadCollection(QStringList pathToImages);
    ImageLabel *imgLabel;

  private:
    QImage qImg;

    std::vector<QImage> imageDataBase;
};

#endif // IMAGE_COLLECTION_H
