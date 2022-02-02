#include "classifier_viewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClassifierViewer w;
    w.show();

    return a.exec();
}
