#ifndef IMAGE_COLLECTION_H
#define IMAGE_COLLECTION_H

#include "image_label.h"

#include <QMainWindow>
#include <QVBoxLayout>


class ImageCollection {

  public:
    ImageCollection();

    void loadCollection();
    void setPathToImages(QStringList newPathToImages);
    void eraseCollectionIfNotEmpty();
    ImageLabel* getImageFromDataBase(int index);
    int getDataBaseSize();

  private:
    QStringList pathToImages;
    std::vector<ImageLabel*> imageDataBase;
};

#endif // IMAGE_COLLECTION_H
