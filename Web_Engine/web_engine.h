#ifndef WEB_ENGINE_H
#define WEB_ENGINE_H

#include <QObject>
#include <QWebEngineView>
#include <QString>
#include <QEventLoop>
#include <QTimer>
#include <QAuthenticator>
#include <QWebEngineDownloadItem>
#include <QWebEngineProfile>
#include <QWebEngineUrlRequestInfo>
#include <QDir>

enum Error{ no_Error, no_Connexion, need_Auth, loading };

class Web_Engine : public QObject
{
    Q_OBJECT

public:
    Web_Engine();
    ~Web_Engine();
    QVariant Set_Javascript(const QString script);
    QString Get_Html();
    QString Get_PlainText();
    bool Load(QString url);
    bool is_Used() const;
    void Stop() const;
    void Show() const;
    void Hide() const;
    void Add_Auth(const QString url,const QString login,const QString password);
    bool Remove_Auth(const QString url);
    int Last_Error() const;
    void Set_Wait_Finished(bool active);
    void Clear();

public slots:
    void Test(QString result = 0);

signals:
    void Progress(int actual);
    void finished(int error);
    void Download_Progress(qint64 actual,qint64 total);
    void Download_Finished(QString url);
    void Get_Finished(const QString &result);

private slots:
    void Load_Finished();
    void Authentication(QUrl url, QAuthenticator *auth);
    void Start_Download(QWebEngineDownloadItem *down);
    void Ending_Download();
    void End_Load();

private:
    void Set_Use(const bool state);
    void Wait(int msec = 30000);
    void Set_Error(const int error);

    QWebEngineView *_web;
    QEventLoop *_loop;
    QTimer *_timer;
    bool _used;
    bool _wait_Finished;
    int _error;
    QList<QStringList> _auth;
    QString _down_Path;
};

#endif // WEB_ENGINE_H
