
#if !defined(__WEB_H__) && defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)
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


