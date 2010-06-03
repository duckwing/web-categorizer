
#ifndef __DBC_H__
#define __DBC_H__

#if defined(QT_CORE_LIB)

#include <QtCore/QObject>

#include "request.h"

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
    void reply(SReq* req);

signals:
    void request(SReq* data);
};

#endif // defined(QT_CORE_LIB)
#endif // __DBC_H__


