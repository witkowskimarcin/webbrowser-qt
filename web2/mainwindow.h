#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWebEngine>
#include <QtWebEngineCore>
#include <QtWebEngineWidgets>
#include <QTableWidget>
#include <QtWebView/QtWebView>
#include <QtWebChannel>
#include <QMessageBox>
#include "historydialog.h"
#include "favouritedialog.h"
#include "favourite.h"
#include "addfavouritedialog.h"
#include "historyitem.h"
#include "sourcecodedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:



private slots:

    void titleChanged(const QString &title);

    void pageTitleChanged(const QString &title);

    void urlChanged(const QUrl &url);

    void loadFinished(bool ok);

    void loadStarted();

    void loadProgress(int progress);

    void cookieAdded(const QNetworkCookie &cookie);

    void savePageToHistory();

    void on_goButton_clicked();

    void on_refreshButton_clicked();

    void on_backButton_clicked();

    void checkOrderUrl();

    void on_forwardButton_clicked();

    void on_tabWidget_tabBarClicked(int index);

    void on_actionNew_tab_triggered();

    void on_actionHistory_triggered();

    void on_actionFavourites_triggered();

    void on_actionAdd_to_favourites_triggered();

    void on_pushButton_clicked();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

    void on_actionShow_code_triggered();

    void on_actionExit_triggered();

    void on_actionSave_session_and_exit_triggered();

    void on_actionShow_cookie_triggered();

    void on_actionSave_link_triggered();

private:
    Ui::MainWindow *ui;
    QList<QWebEngineView*> views;
    QList<QWebEnginePage*> pages;
    QWebEngineView* view;
    QSqlDatabase sql;
    bool flag = false;
    bool loaded = false;
    bool savesession = false;
    QString jQuery;

    void setSlot(QWebEngineView* view);
};

#endif // MAINWINDOW_H
