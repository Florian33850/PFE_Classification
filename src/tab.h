#ifndef TAB_H
#define TAB_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QFileDialog>

class Tab : public QWidget
{
    Q_OBJECT
    public:
        Tab(QWidget * parent = nullptr);
        ~Tab();
};
#endif // TAB_H