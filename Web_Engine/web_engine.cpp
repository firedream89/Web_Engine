#include "web_engine.h"

////////////////////////////////
/// Version 1.0
////////////////////////////////


Web_Engine::Web_Engine()
{
    _web = new QWebEngineView;
    _timer = new QTimer;
    _loop = new QEventLoop;

    QDir dir;
    dir.mkdir("Temp");

    Set_Wait_Finished(true);
    _used = false;
    _error = no_Error;

    connect(_web,SIGNAL(loadProgress(int)),this,SIGNAL(Progress(int)));
    connect(_web->page(),SIGNAL(authenticationRequired(QUrl,QAuthenticator*)),this,SLOT(Authentication(QUrl,QAuthenticator*)));
    connect(_web->page()->profile(),SIGNAL(downloadRequested(QWebEngineDownloadItem*)),this,SLOT(Start_Download(QWebEngineDownloadItem*)));

    connect(_timer,SIGNAL(timeout()),_loop,SLOT(quit()));
}

Web_Engine::~Web_Engine()
{
    delete _web;
    delete _loop;
    delete _timer;
    QDir dir;
    dir.setPath("Temp");
    qDebug() << "Remove Temp" << dir.removeRecursively();
}

bool Web_Engine::Load(QString url)
{
    Set_Error(no_Error);
    _used = true;

    if(!url.contains("http://") && !url.contains("https://"))
        url = "http://" + url;

    _web->load(QUrl(url));
    qDebug() << "Load page :" << url;

    if(_wait_Finished)
        Wait(30000);

    return true;
}

void Web_Engine::Show() const
{
    _web->show();
}

void Web_Engine::Hide() const
{
    _web->hide();
}

void Web_Engine::Stop() const
{
    _web->stop();
}

bool Web_Engine::is_Used() const
{
    return _used;
}

QString Web_Engine::Get_Html()
{
    qDebug() << "Get_Html";
    bool end(false);
    QFile f("Temp/Html.txt");
    f.resize(0);
    if(!f.open(QIODevice::WriteOnly))
        qDebug() << "error open file";
    _web->page()->toHtml([&end,&f](const QString &result){ f.write(result.toUtf8()); end = true; });
    while(!end)
        Wait(500);
    f.close();

    return f.fileName();
}

QString Web_Engine::Get_PlainText()
{
    qDebug() << "Get_Plaintext";
    bool end(false);
    QFile f("Temp/Plaintext.txt");
    f.resize(0);
    if(!f.open(QIODevice::WriteOnly))
        qDebug() << "error open file";
    _web->page()->toPlainText([&end,&f](const QString &result){ f.write(result.toUtf8()); end = true; });
    while(!end)
        Wait(500);
    f.close();
    return f.fileName();
}

QVariant Web_Engine::Set_Javascript(const QString script)
{
    qDebug() << "Send Javascript :" << script;
    bool end(false);
    QVariant res;
    _web->page()->runJavaScript(script,[&end,&res](const QVariant &result){ res = result; end = true; });
    while(!end)
        Wait(500);
    return res;
}

void Web_Engine::Set_Use(const bool state)
{
    _used = state;
}

void Web_Engine::Wait(int msec)
{
    qDebug() << "Wait";
    if(msec <= 0)
        msec = 30000;
    _timer->start(msec);
    _loop->exec();
    _timer->stop();
}

void Web_Engine::Load_Finished()
{
    QString test = Get_PlainText();
    if(test.contains("Aucune connexion Internet"))
    {
        emit finished(-1);
        Set_Error(no_Connexion);
    }
    else
        emit finished(0);

    qDebug() << "Load finished" << Last_Error();
    _used = false;
}

void Web_Engine::Authentication(QUrl url,QAuthenticator *auth)
{
    for(int i=0;i<_auth.count();i++)
        if(_auth.at(i).count() == 3 && _auth.at(i).at(0) == url.toString())
        {
            auth->setUser(_auth.at(i).at(1));
            auth->setPassword(_auth.at(i).at(2));
            return;
        }
    Set_Error(need_Auth);
}

void Web_Engine::Add_Auth(const QString url, const QString login, const QString password)
{
    QStringList new_Auth;
    new_Auth.append(url);
    new_Auth.append(login);
    new_Auth.append(password);

    _auth.append(new_Auth);
}

bool Web_Engine::Remove_Auth(const QString url)
{
    for(int i=0;i<_auth.count();i++)
        if(_auth.at(i).at(0) == url)
        {
            _auth.removeAt(i);
            return true;
        }
    return false;
}

void Web_Engine::Set_Error(const int error)
{
    _error = error;
}

int Web_Engine::Last_Error() const
{
    return _error;
}

void Web_Engine::Start_Download(QWebEngineDownloadItem *down)
{
    QDir dir;
    dir.setPath("download");
    if(!dir.exists())
        dir.mkdir("download");

    _down_Path = "download/"+ down->path().split("\\").last().split("/").last();

    down->setPath(_down_Path);
    down->accept();

    connect(down,SIGNAL(downloadProgress(qint64,qint64)),this,SIGNAL(Download_Progress(qint64,qint64)));
    connect(down,SIGNAL(finished()),this,SLOT(Ending_Download()));
}

void Web_Engine::Ending_Download()
{
    emit Download_Finished(_down_Path);
    _down_Path.clear();
}

void Web_Engine::Set_Wait_Finished(bool active)
{
    qDebug() << "Change _wait_Finished to" << active;
    _wait_Finished = active;
    if(active)
    {
        connect(_web,SIGNAL(loadFinished(bool)),_loop,SLOT(quit()));
        disconnect(_web,SIGNAL(loadFinished(bool)),this,SLOT(Load_Finished()));
    }
    else
    {
        disconnect(_web,SIGNAL(loadFinished(bool)),_loop,SLOT(quit()));
        connect(_web,SIGNAL(loadFinished(bool)),this,SLOT(Load_Finished()));
    }
}
