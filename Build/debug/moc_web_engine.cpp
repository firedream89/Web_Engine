/****************************************************************************
** Meta object code from reading C++ file 'web_engine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Web_Engine/web_engine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'web_engine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Web_Engine_t {
    QByteArrayData data[22];
    char stringdata0[233];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Web_Engine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Web_Engine_t qt_meta_stringdata_Web_Engine = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Web_Engine"
QT_MOC_LITERAL(1, 11, 8), // "Progress"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "actual"
QT_MOC_LITERAL(4, 28, 8), // "finished"
QT_MOC_LITERAL(5, 37, 5), // "error"
QT_MOC_LITERAL(6, 43, 17), // "Download_Progress"
QT_MOC_LITERAL(7, 61, 5), // "total"
QT_MOC_LITERAL(8, 67, 17), // "Download_Finished"
QT_MOC_LITERAL(9, 85, 3), // "url"
QT_MOC_LITERAL(10, 89, 12), // "Get_Finished"
QT_MOC_LITERAL(11, 102, 6), // "result"
QT_MOC_LITERAL(12, 109, 4), // "Test"
QT_MOC_LITERAL(13, 114, 13), // "Load_Finished"
QT_MOC_LITERAL(14, 128, 14), // "Authentication"
QT_MOC_LITERAL(15, 143, 15), // "QAuthenticator*"
QT_MOC_LITERAL(16, 159, 4), // "auth"
QT_MOC_LITERAL(17, 164, 14), // "Start_Download"
QT_MOC_LITERAL(18, 179, 23), // "QWebEngineDownloadItem*"
QT_MOC_LITERAL(19, 203, 4), // "down"
QT_MOC_LITERAL(20, 208, 15), // "Ending_Download"
QT_MOC_LITERAL(21, 224, 8) // "End_Load"

    },
    "Web_Engine\0Progress\0\0actual\0finished\0"
    "error\0Download_Progress\0total\0"
    "Download_Finished\0url\0Get_Finished\0"
    "result\0Test\0Load_Finished\0Authentication\0"
    "QAuthenticator*\0auth\0Start_Download\0"
    "QWebEngineDownloadItem*\0down\0"
    "Ending_Download\0End_Load"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Web_Engine[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x06 /* Public */,
       6,    2,   80,    2, 0x06 /* Public */,
       8,    1,   85,    2, 0x06 /* Public */,
      10,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   91,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x2a /* Public | MethodCloned */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    2,   96,    2, 0x08 /* Private */,
      17,    1,  101,    2, 0x08 /* Private */,
      20,    0,  104,    2, 0x08 /* Private */,
      21,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QUrl, 0x80000000 | 15,    9,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Web_Engine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Web_Engine *_t = static_cast<Web_Engine *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Progress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->finished((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->Download_Progress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->Download_Finished((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->Get_Finished((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->Test((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->Test(); break;
        case 7: _t->Load_Finished(); break;
        case 8: _t->Authentication((*reinterpret_cast< QUrl(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        case 9: _t->Start_Download((*reinterpret_cast< QWebEngineDownloadItem*(*)>(_a[1]))); break;
        case 10: _t->Ending_Download(); break;
        case 11: _t->End_Load(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebEngineDownloadItem* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Web_Engine::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Web_Engine::Progress)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Web_Engine::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Web_Engine::finished)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (Web_Engine::*_t)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Web_Engine::Download_Progress)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (Web_Engine::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Web_Engine::Download_Finished)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (Web_Engine::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Web_Engine::Get_Finished)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject Web_Engine::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Web_Engine.data,
      qt_meta_data_Web_Engine,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Web_Engine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Web_Engine::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Web_Engine.stringdata0))
        return static_cast<void*>(const_cast< Web_Engine*>(this));
    return QObject::qt_metacast(_clname);
}

int Web_Engine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void Web_Engine::Progress(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Web_Engine::finished(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Web_Engine::Download_Progress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void Web_Engine::Download_Finished(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void Web_Engine::Get_Finished(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
