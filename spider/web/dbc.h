
#ifndef __DBC_H__
#define __DBC_H__

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtCore/QCoreApplication>

#include <QtCore/QTimer>


class CDbc : public QCoreApplication {
    Q_OBJECT

private:

    QTimer          timer;

public:
    CDbc ( int & argc, char ** argv );

    virtual bool event(QEvent* e);

private slots:
    void scheduler();
};

#endif // defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)
#endif // __DBC_H__


