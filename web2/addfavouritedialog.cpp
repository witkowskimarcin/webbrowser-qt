#include "addfavouritedialog.h"
#include "ui_addfavouritedialog.h"

AddFavouriteDialog::AddFavouriteDialog(QSqlDatabase sql, Favourite fav, int type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFavouriteDialog)
{
    ui->setupUi(this);

    this->sql = sql;
    this->fav = fav;
    this->type=type;

    ui->title->setText(this->fav.title);
    ui->url->setText(this->fav.url);

    if(type==2)
    {
        ui->description->setText(this->fav.description);
    }
}

AddFavouriteDialog::~AddFavouriteDialog()
{
    delete ui;
}

void AddFavouriteDialog::on_buttonBox_accepted()
{
    if(sql.isOpen())
    {
        QString title = ui->title->text();
        QString url = ui->url->text();
        QString description = ui->description->text();
        QSqlQuery q(sql);
        if(type==1)
        {
            q.prepare("INSERT INTO favourites(title,url,description) VALUES(?,?,?)");
            q.bindValue(0,title);
            q.bindValue(1,url);
            q.bindValue(2,description);
            q.exec();
        }
        else if(type==2)
        {
            q.prepare("UPDATE favourites SET title = ?,url = ?, description = ? WHERE id = ?");
            q.bindValue(0,title);
            q.bindValue(1,url);
            q.bindValue(2,description);
            q.bindValue(3,fav.id);
            q.exec();
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText("Błąd łączenia z bazą danych: "+sql.lastError().text());
        msg.exec();
    }
}
