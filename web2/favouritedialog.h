#ifndef FAVOURITEDIALOG_H
#define FAVOURITEDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QListWidgetItem>
#include "favourite.h"
#include "addfavouritedialog.h"

namespace Ui {
class FavouriteDialog;
}

class FavouriteDialog : public QDialog
{
    Q_OBJECT

public:

    bool returnFlag = false;
    QString returnedUrl;

    explicit FavouriteDialog(QSqlDatabase sql, QWidget *parent = nullptr);
    ~FavouriteDialog();

private slots:
    void on_deleteButton_clicked();

    void on_editButton_clicked();

    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_buttonBox_accepted();

private:

    Ui::FavouriteDialog *ui;
    QList<Favourite> favs;
    QSqlDatabase sql;

    void takeData();
    void printData();

};

#endif // FAVOURITEDIALOG_H
