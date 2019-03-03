#include "historydialog.h"
#include "ui_historydialog.h"

HistoryDialog::HistoryDialog(QSqlDatabase sql, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog)
{
    ui->setupUi(this);

    this->sql = sql;
    takeData();
    printData();
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::on_buttonBox_accepted()
{

}

void HistoryDialog::on_list_itemDoubleClicked(QListWidgetItem *item)
{
    returnFlag = true;
    returnedUrl = historylist.at(ui->list->currentRow()).url;
    this->close();
}

void HistoryDialog::on_menu_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    printData();
}

void HistoryDialog::takeData()
{

    if(sql.isOpen())
    {
        QSqlQuery q(sql);
        q.exec("SELECT date FROM history ORDER BY date DESC");

        QMap<QString,int> map;

        while(q.next())
        {
            map[q.value(0).toString()]++;
        }

        QList<QString> list = map.uniqueKeys();
        for(int i = list.size()-1; i>=0; --i)
        {
            ui->menu->addItem(list.at(i));
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText("Błąd łączenia z bazą danych: "+sql.lastError().text());
        msg.exec();
    }

    ui->menu->setCurrentRow(0);
}

void HistoryDialog::printData()
{
    ui->list->clear();

    if(sql.isOpen())
    {
        QSqlQuery q(sql);
        q.prepare("SELECT id,date,title,url FROM history WHERE date = ? ORDER BY id DESC");
        q.bindValue(0,ui->menu->currentItem()->text());
        q.exec();

        //QMessageBox msg;
        //msg.setText(ui->menu->currentItem()->text());
        //msg.exec();

        HistoryItem tmp;
        while(q.next())
        {
            tmp.id = q.value(0).toInt();
            tmp.date = q.value(1).toString();
            tmp.title = q.value(2).toString();
            tmp.url = q.value(3).toString();
            historylist.push_back(tmp);
            ui->list->addItem(tmp.title);
        }
    }
    else
    {
        QMessageBox msg;
        msg.setText("Błąd łączenia z bazą danych: "+sql.lastError().text());
        msg.exec();
    }
}
