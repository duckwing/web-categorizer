
#ifndef __WEB_H__
#define __WEB_H__

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkProxy>

#include "request.h"

class CWeb : public QObject {
    Q_OBJECT

private:

    QNetworkAccessManager       netman;
    QNetworkProxy               netproxy;

public:
    CWeb ();

    // children's interface
    QNetworkAccessManager& manager();

    void request_completed(SReq* req);

public slots:
    void request(SReq* req);

    void die();

signals:
    void reply(SReq* req);
};

#endif // defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)
#endif // __WEB_H__


