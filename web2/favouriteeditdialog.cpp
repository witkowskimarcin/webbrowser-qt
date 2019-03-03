#include "favouriteeditdialog.h"
#include "ui_favouriteeditdialog.h"

FavouriteEditDialog::FavouriteEditDialog(QSqlDatabase sql, Favourite fav, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FavouriteEditDialog)
{
    ui->setupUi(this);
    this->sql = sql;
    ui->title->setText(fav.title);
    ui->url->setText(fav.url);
    ui->description->setText(fav.description);
}

FavouriteEditDialog::~FavouriteEditDialog()
{
    delete ui;
}

void FavouriteEditDialog::on_buttonBox_accepted()
{

}
