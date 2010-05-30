
#ifndef __SQL_EXC_H__
#define __SQL_EXC_H__

class SqlHandle;

class SqlException {
private:
    char        *buffer;
public:
    SqlException(const char* msg);
    SqlException(const char* msg, const SqlHandle* exc);

    ~SqlException();

    const char* message() const ;
};

#include "sql_api.h"

#endif // __SQL_EXC_H__

