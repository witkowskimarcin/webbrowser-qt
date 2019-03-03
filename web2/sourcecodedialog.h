#ifndef SOURCECODEDIALOG_H
#define SOURCECODEDIALOG_H

#include <QDialog>
#include <QtWebEngineWidgets>
#include <QSyntaxHighlighter>
#include "highlighter.h"

namespace Ui {
class SourceCodeDialog;
}

class SourceCodeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SourceCodeDialog(QWebEnginePage* page, QWidget *parent = nullptr);
    ~SourceCodeDialog();

private:
    Ui::SourceCodeDialog *ui;
    QWebEnginePage* page;
    Highlighter* h;
};

#endif // SOURCECODEDIALOG_H
