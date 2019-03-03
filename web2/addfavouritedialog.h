#ifndef ADDFAVOURITEDIALOG_H
#define ADDFAVOURITEDIALOG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "favourite.h"

namespace Ui {
class AddFavouriteDialog;
}

class AddFavouriteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddFavouriteDialog(QSqlDatabase sql, Favourite fav, int type, QWidget *parent = nullptr);
    ~AddFavouriteDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AddFavouriteDialog *ui;
    QSqlDatabase sql;
    Favourite fav;
    int type;
};

#endif // ADDFAVOURITEDIALOG_H
