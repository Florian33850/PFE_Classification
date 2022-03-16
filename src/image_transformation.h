#ifndef IMAGE_TRANSFORMATION_H
#define IMAGE_TRANSFORMATION_H

#include "image_label.h"

class ImageTransformation
{
    public:
        virtual QVector<QImage> runImageTransformation(std::vector<ImageLabel*> *imagePreviewList) = 0;
};

class MirrorImageTransformation : public ImageTransformation
{   
    public:
        MirrorImageTransformation();

        bool horizontalMirror;
        bool verticalMirror;
        
        void changeHorizontalMirrorMode();
        void changeVerticalMirrorMode();

    private:
        QVector<QImage> runImageTransformation(std::vector<ImageLabel*> *imagePreviewList);
        QVector<QImage> imagesToSave;
};

class GrayscaleImageTransformation : public ImageTransformation
{
    public:
        GrayscaleImageTransformation();
    
    private:
        QVector<QImage> runImageTransformation(std::vector<ImageLabel*> *imagePreviewList);
        QVector<QImage> imagesToSave;
};

#endif // IMAGE_TRANSFORMATION_H