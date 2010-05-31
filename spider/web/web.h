
#ifndef __WEB_H__
#define __WEB_H__

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtCore/QCoreApplication>

#include <QtCore/QTimer>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkProxy>


class CWeb : public QCoreApplication {
    Q_OBJECT

private:

    QNetworkAccessManager       netman;
    QNetworkProxy               netproxy;

    QNetworkReply               *netreply;

    QTimer                      timer;
    int                         cnt;

public:
    CWeb ( int & argc, char ** argv );

private slots:
    void timeout();
    void aboutToQuit();
};

#endif // defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)
#endif // __WEB_H__


