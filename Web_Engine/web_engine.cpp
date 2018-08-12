#include "web_engine.h"

////////////////////////////////
/// Version 1.01
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

void Web_Engine::Test(QString result)
{
    static int t(0);

    if(t == 0)
    {
        this->Show();
        qDebug() << "STARTING TEST(WAIT)";
        qDebug() << "TEST Load page" << Load("http://google.fr");
        qDebug() << "TEST Get Plaintext :" << Get_PlainText();
        qDebug() << "TEST Get Html :" << Get_Html();
        qDebug() << "TEST Last error :" << Last_Error();
        qDebug() << "END TEST(WAIT)";
        qDebug() << "STARTING TEST(CONNECT)";
        Set_Wait_Finished(false);
        connect(this,SIGNAL(finished(int)),this,SLOT(Test()));
        qDebug() << "TEST Load page" << Load("http://google.fr");
        qDebug() << "TEST Loading" << is_Used();
        t++;
    }
    else if(t == 1)
    {
        connect(this,SIGNAL(Get_Finished(QString)),this,SLOT(Test()));
        qDebug() << "TEST Loading" << is_Used();
        qDebug() << "TEST Get Html :" << Get_Html();
        t++;
    }
    else if(t == 2)
    {
        qDebug() << "TEST Get Plaintext :" << Get_PlainText();
        t++;
    }
    else if(t == 3)
    {
        disconnect(this,SIGNAL(finished(int)),this,SLOT(Test()));
        disconnect(this,SIGNAL(Get_Finished(QString)),this,SLOT(Test()));
        qDebug() << "TEST Last error :" << Last_Error();
        qDebug() << "END TEST(CONNECT)";
        this->Hide();
        delete this;
        exit(0);
    }
}

bool Web_Engine::Load(QString url)
{
    Set_Error(no_Error);
    Set_Use(true);

    if(!url.contains("http://") && !url.contains("https://"))
        url = "http://" + url;

    _web->load(QUrl(url));
    qDebug() << "Load page :" << url;

    if(_wait_Finished)
    {
        Wait(30000);
        Set_Use(false);
        End_Load();
    }

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

void Web_Engine::Clear()
{
    _web->page()->deleteLater();
}

QString Web_Engine::Get_Html()
{
    qDebug() << "Get_Html";
    if(is_Used())
    {
        Set_Error(loading);
        qDebug() << "Error page is loading";
        emit Get_Finished(0);
        return QString();
    }
    bool end(false);
    QFile f("Temp/Html.txt");
    f.resize(0);

    if(_wait_Finished)
    {
        if(!f.open(QIODevice::WriteOnly))
            qDebug() << "error open file";
        _web->page()->toHtml([&end,&f](const QString &result){
            f.write(result.toUtf8());
            end = true; });
        while(!end)
            Wait(500);
        f.close();
    }
    else
    {
        _web->page()->toHtml([this](const QString &result){
            QFile f("Temp/Html.txt");
            qDebug() << "file open :" << f.open(QIODevice::WriteOnly);
            f.write(result.toUtf8());
            f.close();
            emit Get_Finished(0); });
    }

    return f.fileName();
}

QString Web_Engine::Get_PlainText()
{
    qDebug() << "Get_Plaintext";
    if(is_Used())
    {
        Set_Error(loading);
        qDebug() << "Error page is loading";
        emit Get_Finished(0);
        return QString();
    }
    bool end(false);
    QFile f("Temp/Plaintext.txt");
    f.resize(0);

    if(_wait_Finished)
    {
        if(!f.open(QIODevice::WriteOnly))
            qDebug() << "error open file";
        _web->page()->toPlainText([&end,&f](const QString &result){
            f.write(result.toUtf8());
            end = true; });
        while(!end)
            Wait(500);
        f.close();
    }
    else
    {
        _web->page()->toPlainText([this](const QString &result){
            QFile f("Temp/Plaintext.txt");
            f.open(QIODevice::WriteOnly);
            f.write(result.toUtf8());
            f.close();
            emit Get_Finished(0); });
    }

    return f.fileName();
}

QVariant Web_Engine::Set_Javascript(const QString script)
{
    qDebug() << "Send Javascript :" << script;
    if(is_Used())
    {
        Set_Error(loading);
        qDebug() << "Error page is loading";
        emit Get_Finished(0);
        return QVariant(0);
    }
    bool end(false);
    QVariant res;
    if(_wait_Finished)
    {
        _web->page()->runJavaScript(script,[&end,&res](const QVariant &result){
            res = result;
            end = true; });
        while(!end)
            Wait(500);
    }
    else
    {
        res = 'NULL';
        _web->page()->runJavaScript(script,[this](const QVariant &result){
            emit Get_Finished(result.toString()); });
    }
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

void Web_Engine::End_Load()
{
    Set_Use(false);

    if(!_wait_Finished)
        connect(this,SIGNAL(Get_Finished(QString)),this,SLOT(Load_Finished()));

    Get_PlainText();
    if(_wait_Finished)
        Load_Finished();
}

void Web_Engine::Load_Finished()
{
    QString test;
    if(!_wait_Finished)
        disconnect(this,SIGNAL(Get_Finished(QString)),this,SLOT(Load_Finished()));

    QFile f("Temp/Plaintext.txt");
    f.open(QIODevice::ReadOnly);
    QTextStream flux(&f);
    test = flux.readAll();
    qDebug() << test;

    if(test.contains("ERR_NAME_NOT_RESOLVED"))
    {
        Set_Error(no_Connexion);
        emit finished(-1);
    }
    else
        emit finished(0);

    qDebug() << "Load finished" << Last_Error();
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
        disconnect(_web,SIGNAL(loadFinished(bool)),this,SLOT(End_Load()));
    }
    else
    {
        disconnect(_web,SIGNAL(loadFinished(bool)),_loop,SLOT(quit()));
        connect(_web,SIGNAL(loadFinished(bool)),this,SLOT(End_Load()));
    }
}
