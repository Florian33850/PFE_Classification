#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QLabel>

class ImageLabel : public QLabel {
  Q_OBJECT
public:
  ImageLabel(QWidget *parent = 0);
  ~ImageLabel();

  void setImage(QImage image);
  void updateContent();

protected Q_SLOTS:
  void resizeEvent(QResizeEvent *event) override;

private:
  QImage rawImage;
  QPixmap pixmap;
};

#endif // IMAGE_LABEL_H