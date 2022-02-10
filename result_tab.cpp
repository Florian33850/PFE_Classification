#include "result_tab.h"

ResultTab::ResultTab(Tab *parent)
    : Tab(parent)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);
}