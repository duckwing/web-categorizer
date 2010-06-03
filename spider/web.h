
#ifndef __WEB_H__
#define __WEB_H__

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkProxy>

class CWeb : public QObject {
    Q_OBJECT

private:

    QNetworkAccessManager*      netman;
    QNetworkProxy               netproxy;

public:
    CWeb ();

public slots:
    void request();

    void die();

signals:
    void reply();
};

#endif // __WEB_H__


