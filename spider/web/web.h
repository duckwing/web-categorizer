
#ifndef __WEB_H__
#define __WEB_H__

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkProxy>


class CWeb : public QObject {
    Q_OBJECT

private:

    QNetworkAccessManager       netman;
    QNetworkProxy               netproxy;

public:
    CWeb ();

public slots:
    void incoming();

    void die();
};

#endif // defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)
#endif // __WEB_H__


