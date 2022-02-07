#ifndef IMAGE_COLLECTION_H
#define IMAGE_COLLECTION_H

#include <image_label.h>

#include <QMainWindow>
#include <QVBoxLayout>


class ImageCollection {

  public:
    ImageCollection();

    void loadCollection();
    void setPathToImages(QStringList newPathToImages);
    ImageLabel* getImageFromDataBase(int index);

  private:
    QStringList pathToImages;
    std::vector<ImageLabel*> imageDataBase;
};

#endif // IMAGE_COLLECTION_H
