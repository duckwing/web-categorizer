
#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "spider.h"

class CRequest {
public:
    int         id;
    QUrl        url;

    int         http_status;
    QString     http_reason;
};


#endif // __REQUEST_H__


