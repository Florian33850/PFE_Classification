#ifndef IMAGE_TRANSFORMATION_H
#define IMAGE_TRANSFORMATION_H

#include "image_label.h"

class ImageTransformation
{
    public:
        virtual void runImageTransformation(std::vector<ImageLabel*> *imagePreviewList) = 0;
        virtual ~ImageTransformation() = default;
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
        void runImageTransformation(std::vector<ImageLabel*> *imagePreviewList);
};

class GrayscaleImageTransformation : public ImageTransformation
{
    public:
        GrayscaleImageTransformation();
    
    private:
        void runImageTransformation(std::vector<ImageLabel*> *imagePreviewList);
};

#endif // IMAGE_TRANSFORMATION_H