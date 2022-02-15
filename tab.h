#ifndef TAB_H
#define TAB_H

#include "image_collection.h"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QImage>

class Tab : public QWidget
{
    Q_OBJECT

public:
    explicit Tab(QWidget * parent = nullptr);
    ~Tab();
};
#endif // TAB_H