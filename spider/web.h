
#ifndef __WEB_H__
#define __WEB_H__

#include "spider.h"

class CWeb : public QObject {
    Q_OBJECT

private:

    QNetworkAccessManager*      netman;
    QNetworkProxy               netproxy;

public:
    CWeb ();

    void send_start();

//
// start/stop
//

signals:
    void start();

public slots:
    void stop();

//
// request/reply
//

public slots:
    void request();

signals:
    void reply();
};

#endif // __WEB_H__


