#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->backButton->setDisabled(true);
    ui->forwardButton->setDisabled(true);

    // dodanie karty i widoku
    view = new QWebEngineView(parent);
    setSlot(view);
    ui->tabWidget->addTab(new QTextEdit(),"Nowa karta");
    //views.push_back(view);
    ui->gridLayout->addWidget(view);

    QWebEnginePage* page = new QWebEnginePage();
    view->setPage(page);
    pages.push_back(page);

    // baza
    sql = QSqlDatabase::addDatabase("QSQLITE","base");
    sql.setDatabaseName("base.sqlite3");
    sql.open();

    if(sql.isOpen())
    {
        QSqlQuery query(sql);
        query.exec("CREATE TABLE IF NOT EXISTS favourites (id INTEGER UNIQUE PRIMARY KEY, title TEXT, url TEXT, description TEXT)");
        query.clear();
        query.exec("CREATE TABLE IF NOT EXISTS history (id INTEGER UNIQUE PRIMARY KEY, date TEXT, title TEXT, url TEXT)");

        query.clear();
        query.prepare("SELECT url FROM session");
        query.exec();

        while(query.next())
        {
            //QWebEngineView* newView = new QWebEngineView(this);
            //setSlot(newView);
            QWebEnginePage* page = new QWebEnginePage();
            view->connect(page, &QWebEnginePage::titleChanged, this, &MainWindow::pageTitleChanged);
            //view->setPage(page);


            ui->tabWidget->addTab(new QTextEdit(),query.value(0).toString());
            page->load(query.value(0).toString());
            pages.push_back(page);

            //views.push_back(newView);
            //newView->load(query.value(0).toString());
        }

        checkOrderUrl();
    }
    else
    {
        QMessageBox msg;
        msg.setText("Błąd łączenia z bazą danych: "+sql.lastError().text());
        msg.exec();
    }

    QFile file;
    file.setFileName("jquery.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    file.close();

    qDebug() << "jQuery: ";
    qDebug() << jQuery.size();
}

MainWindow::~MainWindow()
{
    if(!savesession)
    {
        if(sql.isOpen())
        {
            QSqlQuery query(sql);
            query.exec("DROP TABLE IF EXISTS session");
        }
        else
        {
            QMessageBox msg;
            msg.setText("Błąd łączenia z bazą danych: "+sql.lastError().text());
            msg.exec();
        }
    }


    if(view) delete view;
    sql.close();
    delete ui;
}

void MainWindow::setSlot(QWebEngineView *view)
{
    // eventy
    view->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled,true);
    //view->connect(view->page(), &QWebEnginePage::titleChanged, this, &MainWindow::titleChanged);
    view->connect(view, &QWebEngineView::titleChanged, this, &MainWindow::titleChanged);
    view->connect(view, &QWebEngineView::urlChanged, this, &MainWindow::urlChanged);
    view->connect(view, &QWebEngineView::loadFinished, this, &MainWindow::loadFinished);
    view->connect(view, &QWebEngineView::loadStarted, this, &MainWindow::loadStarted);
    view->connect(view, &QWebEngineView::loadProgress, this, &MainWindow::loadProgress);
    view->connect(view->page()->profile()->cookieStore(), &QWebEngineCookieStore::cookieAdded, this, &MainWindow::cookieAdded);
    //view->connect(view, &QWebEngineCookieStore::cookieAdded, this, &MainWindow::cookieAdded);
}

void MainWindow::titleChanged(const QString &title)
{
    //view = views.at(ui->tabWidget->currentIndex());
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),view->title());
    if(flag==true)
    {

        flag = false;
    }
}

void MainWindow::pageTitleChanged(const QString &title)
{

}

void MainWindow::urlChanged(const QUrl &url)
{
    //view = views.at(ui->tabWidget->currentIndex());

    ui->address->setText(url.toString());
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),url.toString());
    flag = true;
}

void MainWindow::loadFinished(bool ok)
{
    if(ok)
    {
        loaded = true;
        savePageToHistory();
        qDebug() << "#############";
        qDebug() << view->url().authority();
        //view->page()->
    }
}

void MainWindow::loadStarted()
{
    loaded = false;
    //checkOrderUrl();
}

void MainWindow::loadProgress(int progress)
{
    if(progress>20)
    {
       checkOrderUrl();
    }
}

void MainWindow::cookieAdded(const QNetworkCookie &cookie)
{
    //qDebug() << "@@@@@@@@@@@@@@@@@@@@@";
    //qDebug() << cookie.domain() << cookie.expirationDate().toString() << cookie.path();
}

void MainWindow::savePageToHistory()
{
    QDate date = QDate::currentDate();

    QString today=QString::number(date.year());
    today.append("-");
    today.append(QString::number(date.month()));
    today.append("-");
    today.append(QString::number(date.day()));

     if(sql.isOpen())
     {
         QSqlQuery q(sql);
         q.prepare("INSERT INTO history(date,title,url) VALUES(?,?,?)");
         q.bindValue(0,today);
         q.bindValue(1,view->title());
         q.bindValue(2,view->url().toString());

         if(q.exec())
         {
             qDebug("Udalo sie");
         }
         else
         {
             qDebug("Nie udalo sie");
         }

     }
     else
     {
         QMessageBox msg;
         msg.setText("Błąd łączenia z bazą danych: "+sql.lastError().text());
         msg.exec();
     }
}

void MainWindow::on_goButton_clicked()
{
    QString address = ui->address->text();
    if(address.length()>0)
    {
        if(!address.contains("http://") && !address.contains("https://"))
        {
            address = "http://" + address;
        }

        ui->refreshButton->setDisabled(false);

        view->page()->load(QUrl(address));
    }
}

void MainWindow::on_refreshButton_clicked()
{
    view->reload();
}

void MainWindow::on_backButton_clicked()
{
    view->back();
}

void MainWindow::on_forwardButton_clicked()
{
    view->forward();
}

void MainWindow::on_actionNew_tab_triggered()
{

//    QWebEngineView* newView = new QWebEngineView(this->parentWidget());
//    setSlot(newView);
//    views.push_back(newView);
//    ui->tabWidget->addTab(newView,"Nowa karta");
//    checkOrderUrl();

    QWebEnginePage* page = new QWebEnginePage();
    view->connect(page, &QWebEnginePage::titleChanged, this, &MainWindow::pageTitleChanged);
    //view->setPage(page);


    ui->tabWidget->addTab(new QTextEdit(),"Nowa karta");
    pages.push_back(page);
}

void MainWindow::on_actionHistory_triggered()
{
    HistoryDialog h(sql, this);
    h.exec();
    if(h.returnFlag)
    {
        view->load(QUrl(h.returnedUrl));
    }
}

void MainWindow::on_actionFavourites_triggered()
{
    FavouriteDialog f(sql,this);
    f.exec();
    if(f.returnFlag)
    {
        view->load(QUrl(f.returnedUrl));
    }
}

void MainWindow::on_actionAdd_to_favourites_triggered()
{
    Favourite fav;
    fav.title = view->title();
    fav.url = view->url().toString();
    AddFavouriteDialog a(sql,fav,1,this);
    a.exec();
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::checkOrderUrl()
{
    //t = tabs.at(ui->tabWidget->currentIndex());

    if(view->history()->canGoBack())
    {
        ui->backButton->setDisabled(false);
    }
    else
    {
        ui->backButton->setDisabled(true);
    }

    if(view->history()->canGoForward())
    {
        ui->forwardButton->setDisabled(false);
    }
    else
    {
        ui->forwardButton->setDisabled(true);
    }
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if(ui->tabWidget->count()>0 && pages.size()>0)
    {
        pages.removeAt(index);
        ui->tabWidget->removeTab(index);
    }

    if(ui->tabWidget->count()==0 && pages.size()==0)
    {
        //view = new QWebEngineView(this);

        //setSlot(view);

        ui->tabWidget->addTab(new QTextEdit(),"Nowa karta");

        QWebEnginePage* page = new QWebEnginePage();
        view->connect(page, &QWebEnginePage::titleChanged, this, &MainWindow::pageTitleChanged);
        pages.push_back(page);
        view->setPage(page);
        ui->address->setText("");
    }
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{

}


void MainWindow::on_tabWidget_currentChanged(int index)
{
//    if(views.size()>0 && views.size()>index)
//    {
//        ui->address->setText(views.at(index)->url().toString());
//        view = views.at(index);
//    }

    if(pages.size()>0 && pages.size()>index)
    {
        ui->address->setText(pages.at(index)->url().toString());
        if(pages.at(index)->title().length()>0)
       ui->tabWidget->setTabText(index,pages.at(index)->title());
        view->setPage(pages.at(index));
    }

    checkOrderUrl();
}

void MainWindow::on_actionShow_code_triggered()
{
    //QWebEnginePage::WebAction a = view->page()->ViewSource;
    //view->page()->scripts().toList().at(0).sourceCode()
    //view->setPage(view->page()->inspectedPage());

 //   QMessageBox msg;
    //const QString& str = "";
    //const QWebEngineCallback<const QString&> result(const QString& str);

       //view->page()->toPlainText(result);
        //msg.setText(str);
        //msg.exec();


//    view->page()->toHtml([this] (const QString &result)
//    {
//        qDebug() << "HTML: ";
//        qDebug() << result;
//    });

//    view->page()->toPlainText([] (const QString &result)
//    {
//        qDebug() << "PlainText: " << result;
//    });


//    QTextEdit *te = new QTextEdit;

//    view->page()->toHtml( [te] (const QString &result){ te->setPlainText(result); });
//    view->page()->toPlainText( [te] (const QString &result){ te->setPlainText(result); });



    //ui->textEdit->setPlainText(te->toPlainText());

    //QMessageBox msg;
    //msg.setText(te->toHtml());
    //msg.exec();



    SourceCodeDialog dialog(view->page());
    dialog.exec();
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionSave_session_and_exit_triggered()
{
    this->close();
    savesession=true;

    if(sql.isOpen())
    {
        QSqlQuery query(sql);
        query.exec("DROP TABLE IF EXISTS session");
        query.clear();
        query.exec("CREATE TABLE IF NOT EXISTS session (id INTEGER UNIQUE PRIMARY KEY, url TEXT)");

        foreach(QWebEnginePage* v, pages)
        {
            QSqlQuery q(sql);

            q.prepare("INSERT INTO session(url) VALUES(?)");
            q.bindValue(0,v->url().toString());
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

void MainWindow::on_actionShow_cookie_triggered()
{
    //qDebug() << view->page()->profile()->cookieStore();
    //qDebug() << view->page()->profile()->cachePath();

    QString script = QStringLiteral("qt.jQuery('form').serializeArray()");
    view->page()->runJavaScript(jQuery);
    view->page()->runJavaScript(script);
}

void MainWindow::on_actionSave_link_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Link"), "",
        tr("Link (*.URL)"));

    QFile plik(fileName);

    if(plik.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream zapis(&plik);
        QString linia;

        linia = "URL="+view->url().toString();
        zapis << "[InternetShortcut]\n";
        zapis << linia;
    }

    plik.close();

}
