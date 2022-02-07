#ifndef CLASSIFIER_VIEWER_H
#define CLASSIFIER_VIEWER_H

#include "image_collection.h"
#include "image_label.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QImage>
#include <QLabel>

class ClassifierViewer : public QMainWindow {
  Q_OBJECT

public:
  ClassifierViewer(QWidget * parent = 0);
  ~ClassifierViewer();

public slots:
  void selectDataBaseFiles();
  
private:
  QWidget *mainWidget;
  QVBoxLayout *mainLayout;

  ImageCollection *imgCollection;

  void settingMenu(ClassifierViewer *classifierViewer);
  void openDataBaseButton(QMenu *menu = NULL);
};

#endif // CLASSIFIER_VIEWER_H
