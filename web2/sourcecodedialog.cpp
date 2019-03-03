#include "sourcecodedialog.h"
#include "ui_sourcecodedialog.h"

SourceCodeDialog::SourceCodeDialog(QWebEnginePage* page, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SourceCodeDialog)
{
    ui->setupUi(this);
    this->page=page;

    //ui->textEdit->setText(page->inspectedPage());

//    QTextEdit *te = new QTextEdit;
//    page->toHtml( [te] (const QString &result){ te->setPlainText(result); });
//    page->toPlainText( [te] (const QString &result){ te->setPlainText(result); });

//    ui->textEdit->setPlainText(te->toPlainText());

//    QMessageBox msg;
//    msg.setText(te->toPlainText());
//    msg.exec();





    page->toHtml([this] (const QString &result)
    {
        //qDebug() << "HTML: ";
        //qDebug() << result;
        h = new Highlighter(ui->textEdit->document());
        ui->textEdit->setPlainText(result);

        //ui->textEdit->setText(result);
        //ui->textEdit->setHtml("<html><head></head><body>xddd</body></html>");
    });


    //ui->textEdit->show();

//    QTextCharFormat fmt;
//    fmt.setBackground(Qt::yellow);

//    QTextCursor cursor(ui->textEdit->document());
//    cursor.setPosition(10,QTextCursor::MoveAnchor );
//    cursor.setPosition(20,QTextCursor::KeepAnchor);
//    cursor.setCharFormat(fmt);
}

SourceCodeDialog::~SourceCodeDialog()
{
    delete ui;
}
