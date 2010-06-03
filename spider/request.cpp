
#include "request.h"
#include "utils.h"

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

CRequest::CRequest(CWeb* _web, SReq* _req):
    QObject(_web),

    web(_web),
    req(_req)
{
    // 
    QNetworkAccessManager&  netman = web->manager();

    // ask the network manager to fetch the url
    //req->reply = netman.get(QNetworkRequest(QUrl(QString(req->url.c_str()))));

    // connect the finished signal to self
    //connect(req->reply, SIGNAL(finished()), SLOT(finished()));
}

CRequest::~CRequest(){
    // if req != 0, then the request has not finished yet
    // NOTE: req->reply is a child of the manager, it will be removed separately
    if(req) delete req;
}

//
// slots
//

void CRequest::finished(){
    cout << "request finished\n";

    // tell the web that the request has completed
    web->request_completed(req);
    
    // unlink the request from self and die
    req = 0;
    delete this;
}

#endif


