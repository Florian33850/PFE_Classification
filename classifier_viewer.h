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
  
private:
  QVBoxLayout *mainLayout;
  QWidget *mainWidget;
  QTabWidget *tabWidget;


  void settingMenu(ClassifierViewer *classifierViewer);
  void openDataBaseButton(QMenu *menu = NULL);
};

class DataloaderTab : public QWidget
{
    Q_OBJECT
public:
    int maxNumberOfImageToDisplay;

    explicit DataloaderTab( QWidget *parent = nullptr);
    void displayDataBaseImages();
    bool selectDataBasePath();

public slots:
    void handleLoadDataBaseButton();

private:
    ImageCollection *imgCollection;
    QVBoxLayout *mainLayout;

    void updateWindow();
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
