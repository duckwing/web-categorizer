
#ifndef __SQL_EXC_H__
#define __SQL_EXC_H__

#include "sql_api.h"


class SqlException {
private:
    SQLCHAR     *buffer;                // TODO: reimplement via char *
public:
    SqlException(const char* msg);
    SqlException(const char* msg, const SqlHandle& exc);

    ~SqlException();

    SQLCHAR* message() const ;
};

#endif // __SQL_EXC_H__

