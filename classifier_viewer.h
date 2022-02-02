#ifndef CLASSIFIER_VIEWER_H
#define CLASSIFIER_VIEWER_H

#include <QMainWindow>
#include <QVBoxLayout>

class ClassifierViewer : public QMainWindow {
  Q_OBJECT

 public:
  ClassifierViewer(QWidget * parent = 0);
  ~ClassifierViewer();

 private:
  QWidget *mainWidget;
  QVBoxLayout *mainLayout;

  void settingMenu(ClassifierViewer *classifierViewer);
  
};

#endif // CLASSIFIER_VIEWER_H
