#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QString>

class HistoryItem
{
public:

    int id;
    QString url;
    QString title;
    QString date;

    HistoryItem();
};

#endif // HISTORYITEM_H
