#ifndef SAVELINKDIALOG_H
#define SAVELINKDIALOG_H

#include <QDialog>

namespace Ui {
class SaveLinkDialog;
}

class SaveLinkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveLinkDialog(QWidget *parent = nullptr);
    ~SaveLinkDialog();

private:
    Ui::SaveLinkDialog *ui;
};

#endif // SAVELINKDIALOG_H
