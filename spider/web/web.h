
#ifndef __WEB_H__
#define __WEB_H__

#include <QtCore/QCoreApplication>

#include <QtCore/QTimer>


class CWeb : public QCoreApplication {
    Q_OBJECT

private:
    QTimer      timer;
    int         cnt;

public:
    CWeb ( int & argc, char ** argv );

private slots:
    void timeout();
    void aboutToQuit();
};

#endif // __WEB_H__


