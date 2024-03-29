
#ifndef __WEB_H__
#define __WEB_H__

#include "spider.h"

#include "request.h"

class CWeb : public QObject {
    Q_OBJECT

private:

    QNetworkAccessManager*              netman;
    QNetworkProxy                       netproxy;

    map<QNetworkReply*, CRequest*>      reply_map;

private slots:
    void request_finished(QNetworkReply * reply);

public:
    CWeb ();
    ~CWeb();

//
// start/stop
//

public slots:
    void start();

signals:
    void started();

//
// request/reply
//

public slots:
    void request(CRequest *req);

signals:
    void reply(CRequest *req);
};

#endif // __WEB_H__


