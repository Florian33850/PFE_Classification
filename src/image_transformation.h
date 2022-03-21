#ifndef IMAGE_TRANSFORMATION_H
#define IMAGE_TRANSFORMATION_H

#include "image_label.h"

class ImageTransformation
{
    public:
        void runImageTransformationOnPreviewList(std::vector<ImageLabel*> *imagePreviewList);
        virtual QImage applyImageTransformation(QImage qImage) = 0;
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
        QImage applyImageTransformation(QImage qImage);

};

class GrayscaleImageTransformation : public ImageTransformation
{
    public:
        GrayscaleImageTransformation();
    
    private:
        QImage applyImageTransformation(QImage qImage);
};

#endif // IMAGE_TRANSFORMATION_H