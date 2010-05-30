
#ifndef __SQL_CONN_H__
#define __SQL_CONN_H__

#include "sql_api.h"

class SqlConn : public SqlHandle {
public:
    SqlConn(const SqlEnv& env);

    ~SqlConn();
};

#endif // __SQL_CONN_H__


