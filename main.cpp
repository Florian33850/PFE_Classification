#include "application_viewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ApplicationViewer w;
    w.show();

    return a.exec();
}
