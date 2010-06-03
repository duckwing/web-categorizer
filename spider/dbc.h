
#ifndef __DBC_H__
#define __DBC_H__

#include "spider.h"

class CDbc : public QObject {
    Q_OBJECT

private:

private slots:
    void scheduler();

    // public

public:
    CDbc ();

//
// start/stop
//

public slots:
    void start();
    void stop();

//
// request/reply
//

signals:
    void request();

public slots:
    void reply();

};

#endif // __DBC_H__


