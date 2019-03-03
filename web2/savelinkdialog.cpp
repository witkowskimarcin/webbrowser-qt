#include "savelinkdialog.h"
#include "ui_savelinkdialog.h"

SaveLinkDialog::SaveLinkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveLinkDialog)
{
    ui->setupUi(this);
}

SaveLinkDialog::~SaveLinkDialog()
{
    delete ui;
}
