#include "favouritedialog.h"
#include "ui_favouritedialog.h"

FavouriteDialog::FavouriteDialog(QSqlDatabase sql, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FavouriteDialog)
{
    ui->setupUi(this);

    this->sql=sql;

    takeData();
    printData();
}

FavouriteDialog::~FavouriteDialog()
{
    delete ui;
}

void FavouriteDialog::takeData()
{
    if(sql.isOpen())
    {
        QSqlQuery q(sql);
        q.exec("SELECT id,title,url,description FROM favourites");

        Favourite tmp;
        while(q.next())
        {
            tmp.id = q.value(0).toInt();
            tmp.title = q.value(1).toString();
            tmp.url = q.value(2).toString();
            tmp.description = q.value(3).toString();
            favs.push_back(tmp);
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText("Błąd łączenia z bazą danych: "+sql.lastError().text());
        msg.exec();
    }
}

void FavouriteDialog::printData()
{
    foreach(Favourite item,favs)
    {
        ui->listWidget->addItem(item.title);
    }

    if(favs.size()>0)
    {
        ui->listWidget->setCurrentRow(0);
    }
    else
    {
        ui->deleteButton->setDisabled(true);
        ui->editButton->setDisabled(true);

    }
}

void FavouriteDialog::on_deleteButton_clicked()
{
    QMessageBox::StandardButton question;

    question = QMessageBox::question(this,"Usuwanie zakładki", "Czy na pewno chcesz usunąc zakładkę?",QMessageBox::Yes | QMessageBox::No);

    if(question == QMessageBox::Yes)
    {
        if(sql.isOpen())
        {
            int id = favs.at(ui->listWidget->currentRow()).id;
            QSqlQuery q(sql);
            q.prepare("DELETE FROM favourites WHERE id = ?");
            q.bindValue(0,id);
            q.exec();
        }
        else
        {
            QMessageBox msg;
            msg.setText("Błąd łączenia z bazą danych: "+sql.lastError().text());
            msg.exec();
        }

        ui->listWidget->clear();
        favs.clear();
        takeData();
        printData();
    }
}

void FavouriteDialog::on_editButton_clicked()
{
    AddFavouriteDialog a(sql,favs.at(ui->listWidget->currentRow()),2,this);
    a.exec();
    ui->listWidget->clear();
    favs.clear();
    takeData();
    printData();
}

void FavouriteDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    returnFlag = true;
    returnedUrl = favs.at(ui->listWidget->currentRow()).url;
    this->close();
}

void FavouriteDialog::on_buttonBox_accepted()
{
    //returnFlag = true;
    //returnedUrl = favs.at(ui->listWidget->currentRow()).url;
}
