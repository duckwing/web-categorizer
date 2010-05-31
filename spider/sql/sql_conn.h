
#ifndef __SQL_CONN_H__
#define __SQL_CONN_H__

#include "sql_api.h"

class SqlConn : public SqlHandle {
private:
    bool        connected;
public:
    SqlConn(const SqlEnv& env);

    ~SqlConn();

    void connect();
    void disconnect();
};

#endif // __SQL_CONN_H__


