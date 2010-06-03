
#ifndef __REQUEST_H__
#define __REQUEST_H__

#include "spider.h"

class CRequest : public QObject {
    Q_OBJECT

public:
    QUrl        url;

};


#endif // __REQUEST_H__


