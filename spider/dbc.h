
#ifndef __DBC_H__
#define __DBC_H__

#include "spider.h"

#include "request.h"

class CDbc : public QObject {
    Q_OBJECT

private:
    QSqlQuery       *q1;
    QSqlQuery       *q2;

    int             req_avail;

    bool open_db();

private slots:
    void scheduler();

    // public

public:
    CDbc ();
    ~CDbc();

//
// start/stop
//

public slots:
    void start();
    //void stop();

//
// request/reply
//

signals:
    void request(CRequest* req);

public slots:
    void reply(CRequest* req);

};

#endif // __DBC_H__


