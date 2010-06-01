
#ifndef __REQUEST_H__
#define __REQUEST_H__

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)


//////////////////////////////
// some useful data structures
//

#include <QtNetwork/QNetworkReply>

#include "utils.h"

struct SReq {
    int                 id;
    string              url;
    QNetworkReply       *reply;
};

///////////////////////////

class CRequest : public QObject {
    Q_OBJECT
 
private:
    SRequest*       req;
public:
    CRequest(SReq* _req, QObject* _p = 0);
    ~CRequest();

private slots:
    void finished();
};


#endif // defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#endif // __REQUEST_H__


