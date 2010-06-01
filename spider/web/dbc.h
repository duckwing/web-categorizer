
#ifndef __DBC_H__
#define __DBC_H__

#if defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)

#include <QtCore/QCoreApplication>

#include <QtCore/QThread>
#include <QtCore/QTimer>


class CDbc : public QCoreApplication {
    Q_OBJECT

private:

    QTimer          timer;

    QThread         worker;

public:
    CDbc ( int & argc, char ** argv );

    virtual bool event(QEvent* e);

private slots:
    void scheduler();

    void worker_finished();

signals:
    void worker_send();
    void worker_die();
};

#endif // defined(QT_CORE_LIB) && defined(QT_NETWORK_LIB)
#endif // __DBC_H__


