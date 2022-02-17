#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QLabel>
#include <QImage>

class ImageLabel : public QLabel {
  Q_OBJECT
public:
  ImageLabel(QWidget *parent = 0);
  ~ImageLabel();

  void updateContent();
  void setImage(QImage image);
  QImage getQImage();

protected Q_SLOTS:
  void resizeEvent(QResizeEvent *event) override;

private:
  QImage rawImage;
  QPixmap pixmap;
};

#endif // IMAGE_LABEL_H