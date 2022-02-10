#include "image_label.h"

ImageLabel::ImageLabel(QWidget *parent) : QLabel(parent) {
  QSizePolicy size_policy;
  size_policy.setVerticalPolicy(QSizePolicy::Minimum);
  size_policy.setHorizontalPolicy(QSizePolicy::Minimum);
  setSizePolicy(size_policy);
  setMinimumSize(100, 100);
}

ImageLabel::~ImageLabel() {}

void ImageLabel::setImage(QImage image)
{
  rawImage = image;
  updateContent();
}

void ImageLabel::updateContent()
{
  if (rawImage.isNull())
  {
    return;
  }
  pixmap = QPixmap::fromImage(rawImage);
  pixmap = pixmap.scaled(this->size(), Qt::KeepAspectRatio);
  setPixmap(pixmap);
}

void ImageLabel::resizeEvent(QResizeEvent *event)
{
  (void)event;
  updateContent();
}
