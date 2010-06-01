
#ifndef __DBC_H__
#define __DBC_H__

#if defined(QT_CORE_LIB)

#include <QtCore/QObject>

#include "request.h"

class CDbc : public QObject {
    Q_OBJECT

private:

public:
    CDbc ();

public slots:
    void start();
    void stop();

    void reply(SReq* req);

private slots:
    void scheduler();

signals:
    void request(SReq* data);
};

#endif // defined(QT_CORE_LIB)
#endif // __DBC_H__


