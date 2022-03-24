#include "image_label.h"

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent) {
    QSizePolicy size_policy;
    size_policy.setVerticalPolicy(QSizePolicy::Minimum);
    size_policy.setHorizontalPolicy(QSizePolicy::Minimum);
    this->setSizePolicy(size_policy);
    this->setMinimumSize(MINIMUM_IMAGE_WIDTH_IMAGE_LABEL, MINIMUM_IMAGE_HEIGHT_IMAGE_LABEL);
}

ImageLabel::~ImageLabel() {}

void ImageLabel::updateContent()
{
    if (this->qImage.isNull())
    {
        return;
    }
    this->pixmap = QPixmap::fromImage(this->qImage);
    this->pixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio);
    this->setPixmap(this->pixmap);
}

void ImageLabel::resizeEvent(QResizeEvent *event)
{
    (void)event;
    updateContent();
}