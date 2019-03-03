#ifndef FAVOURITEEDITDIALOG_H
#define FAVOURITEEDITDIALOG_H

#include <QDialog>
#include <QtSql>
#include "favourite.h"

namespace Ui {
class FavouriteEditDialog;
}

class FavouriteEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FavouriteEditDialog(QSqlDatabase sql, Favourite fav, int type, QWidget *parent = nullptr);
    ~FavouriteEditDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::FavouriteEditDialog *ui;
    QSqlDatabase sql;
    int type;
};

#endif // FAVOURITEEDITDIALOG_H
