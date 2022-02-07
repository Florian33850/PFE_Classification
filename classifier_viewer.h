#ifndef CLASSIFIER_VIEWER_H
#define CLASSIFIER_VIEWER_H

#include <QMainWindow>
#include <QVBoxLayout>

#include "model_runner.h"

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

class DataloaderTab : public QWidget
{
    Q_OBJECT

public:
    explicit DataloaderTab( QWidget *parent = nullptr);
};

class ClassificationTrainingTab : public QWidget
{
    Q_OBJECT

public:
    explicit ClassificationTrainingTab(QWidget *parent = nullptr);
};

class ExperimentationTab : public QWidget
{
    Q_OBJECT

public:
    explicit ExperimentationTab(QWidget *parent = nullptr);
};
#endif // CLASSIFIER_VIEWER_H
