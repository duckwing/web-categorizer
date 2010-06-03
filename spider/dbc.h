
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

    // control stuff

public slots:
    void start();
    void stop();

    // data exchange

public slots:
    void reply();

signals:
    void request();
};

#endif // __DBC_H__


