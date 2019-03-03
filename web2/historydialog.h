#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QtSql>
#include <QMessageBox>
#include "historyitem.h"

namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog
{
    Q_OBJECT

public:

    bool returnFlag=false;
    QString returnedUrl;

    explicit HistoryDialog(QSqlDatabase sql, QWidget *parent = nullptr);
    ~HistoryDialog();

private slots:
    void on_buttonBox_accepted();

    void on_list_itemDoubleClicked(QListWidgetItem *item);

    void on_menu_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::HistoryDialog *ui;
    QSqlDatabase sql;
    QList<HistoryItem> historylist;
    QMultiMap<QString,HistoryItem> historymap;

    void takeData();
    void printData();
};

#endif // HISTORYDIALOG_H
