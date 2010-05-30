
#ifndef __SQL_ENV_H__
#define __SQL_ENV_H__

#include "sql_api.h"

class SqlEnv : public SqlHandle {
public:
    SqlEnv();

    // methods

    SQLRETURN set_attr(SQLINTEGER attr, SQLPOINTER value, SQLINTEGER len = 0);

};

#endif // __SQL_ENV_H__

