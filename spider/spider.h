
#ifndef __UTILS_H__
#define __UTILS_H__

//
// This header is intended to be precompiled
//

//
// STL
//

#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

//
// Qt
//

#include <QtCore>
#include <QtNetwork>
#include <QtSql>

//
// utils
//

#define sizeof_a(a)     (sizeof(a)/sizeof(a[0]))

#define DIRECT_CONNECT(sender, signal, receiver, slot, signature)   \
    QObject::connect(sender, SIGNAL(signal signature), receiver, SLOT(slot signature), Qt::DirectConnection)

#define QUEUED_CONNECT(sender, signal, receiver, slot, signature)   \
    QObject::connect(sender, SIGNAL(signal signature), receiver, SLOT(slot signature), Qt::QueuedConnection)

#endif // __UTILS_H__

