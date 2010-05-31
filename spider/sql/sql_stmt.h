
#ifndef __SQL_STMT_H__
#define __SQL_STMT_H__

#include "sql_api.h"

class SqlStmt : public SqlHandle {
public:
    SqlStmt(const SqlConn& conn);

    // bind

    SQLRETURN bindcol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValuePtr, SQLINTEGER BufferLength, SQLLEN *StrLen_or_Ind);

    // attributes

    SQLRETURN set_attr(SQLINTEGER attr, SQLPOINTER ptr, SQLINTEGER len);

    // statement

    SQLRETURN fetch();
    SQLRETURN direct(SQLWCHAR* text);

    // long data

    SQLRETURN get_data(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValuePtr, SQLINTEGER BufferLength, SQLINTEGER *StrLen_or_IndPtr); 

    // utils
    
    SQLRETURN bind_param_offset(SQLINTEGER* ptr);
    SQLRETURN bind_row_offset(SQLINTEGER* ptr);
};

#endif // __SQL_STMT_H__

