
#include "sql_env.h"

SqlEnv::SqlEnv() : SqlHandle(0, SQL_HANDLE_ENV) {
    SQLHANDLE   h;

    switch (sql_api.SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &handle)){
        case SQL_SUCCESS: case SQL_SUCCESS_WITH_INFO: break;
        default: throw "SQLAllocHandle(SQL_HANDLE_ENV) failed";
    }

    set_attr(SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3);
}


SQLRETURN SqlEnv::set_attr(SQLINTEGER attr, SQLPOINTER value, SQLINTEGER len = 0){
    SQLRETURN rc;

    SQLAPI(SQLSetEnvAttr, (*this, attr, value, len), *this);

    return rc;
}



