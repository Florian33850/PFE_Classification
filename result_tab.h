#ifndef RESULT_TAB_H
#define RESULT_TAB_H

#include "tab.h"

class ResultTab : public Tab
{
    Q_OBJECT

public:
    explicit ResultTab(Tab *parent = nullptr);
};
#endif // RESULT_TAB_H