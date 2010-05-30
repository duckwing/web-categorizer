
#ifndef __SQL_STMT_H__
#define __SQL_STMT_H__

#include "sql_api.h"

class SqlStmt : public SqlHandle {
public:
    SqlStmt(const SqlConn& conn);

    // bind

    SQLRETURN bindcol(SQLUSMALLINT ColumnNumber, SQLSMALLINT TargetType, SQLPOINTER TargetValuePtr, SQLINTEGER BufferLength, SQLLEN *StrLen_or_Ind);

    // statement

    SQLRETURN fetch();
    SQLRETURN direct(SQLWCHAR* text);
};

#endif // __SQL_STMT_H__

