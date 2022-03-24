#ifndef PREPROCESSING_TAB_H
#define PREPROCESSING_TAB_H

#include "tab.h"

#include <QFileDialog>

class PreprocessingTab : public Tab
{
    Q_OBJECT
    public:
        PreprocessingTab();

        void addSaveButton();
        void handleNewDataHandler(DataHandler *dataHandler);
};
#endif // PREPROCESSING_TAB_H