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
        Tab();
        ~Tab();

        void clearLayout(QLayout *layout);
};
#endif // TAB_H