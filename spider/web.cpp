

#include "web.h"

CWeb::CWeb() :
    QObject (),

    netman(0),
    netproxy(QNetworkProxy::Socks5Proxy, "127.0.0.1", 4000)

{
}

CWeb::~CWeb(){
    cout << "web dies\n";

    {
        map<QNetworkReply*, CRequest*>::iterator        i, i2;

        for(i = reply_map.begin(), i2 = reply_map.end(); i != i2; i++){
            delete i->second;
        }
    }
}

void CWeb::request_finished(QNetworkReply * r){
    CRequest *req = 0;

    {
        map<QNetworkReply*, CRequest*>::iterator    it = reply_map.find(r);

        if(it == reply_map.end()){
            cout << "map error\n";
            return;
        }

        req = it->second;

        reply_map.erase(it);
    }

    // automatically follow redirects
    {
        QVariant var = r->attribute(QNetworkRequest::RedirectionTargetAttribute);

        if(var.isValid()){
            r->deleteLater();

            r = netman->get(QNetworkRequest(var.toUrl()));

            pair<QNetworkReply*, CRequest*>     p(r, req);
            reply_map.insert(p);
            return;
        }
    }

    // do something
    req->http_status = r->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    req->http_reason = r->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
    req->http_redirect = QString(); //r->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl().toString();

    r->deleteLater();

    emit reply(req);
}

void CWeb::start(){
    netman = new QNetworkAccessManager(this);

    DIRECT_CONNECT(netman, finished, this, request_finished, (QNetworkReply*));

    // setup network
    //netman->setProxy(netproxy);
    //netproxy.setCapabilities(QNetworkProxy::HostNameLookupCapability);

    cout << "web send start\n";
    emit started();
}


//
// slots
//

void CWeb::request(CRequest *req){
    cout << "incoming: " << req->url.toString().toAscii().data() << endl;

    QNetworkReply *r = netman->get(QNetworkRequest(req->url));

    pair<QNetworkReply*, CRequest*>     p(r, req);
    reply_map.insert(p);
}


