#include <QtTest/QtTest>

#include "../src/images_preview_widget.h"

class ImagesPreviewWidgetTests: public QObject
{
    Q_OBJECT

    private Q_SLOTS:
        void testImagesPreviewWidgetInstantiation();
};

void ImagesPreviewWidgetTests::testImagesPreviewWidgetInstantiation()
{
    std::vector<ImageLabel*> *imagePreviewList = new std::vector<ImageLabel*>();
    ImagesPreviewWidget *imagesPreviewWidget = new ImagesPreviewWidget(imagePreviewList);
    QVERIFY(imagesPreviewWidget != NULL);
}

QTEST_MAIN(ImagesPreviewWidgetTests)
#include "images_preview_widget_test.moc"
