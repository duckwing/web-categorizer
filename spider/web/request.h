
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

class CWeb;

class CRequest : public QObject {
    Q_OBJECT
 
private:
    CWeb            *web;
    SReq            *req;
public:
    CRequest(CWeb* _web, SReq* _req);
    ~CRequest();

public slots:
    void finished();
};

#include "web.h"

#endif // defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#endif // __REQUEST_H__


