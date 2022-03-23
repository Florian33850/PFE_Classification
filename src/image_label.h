#ifndef IMAGE_LABEL_H
#define IMAGE_LABEL_H

#include <QLabel>
#include <QImage>

#define MINIMUM_IMAGE_WIDTH 100
#define MINIMUM_IMAGE_HEIGHT 100

class ImageLabel : public QLabel
{
    Q_OBJECT
    public:
        ImageLabel(QWidget *parent = 0);
        ~ImageLabel();

        QImage qImage;

        void updateContent();

    protected Q_SLOTS:
        void resizeEvent(QResizeEvent *event) override;

    private:
        QPixmap pixmap;
};
#endif // IMAGE_LABEL_H