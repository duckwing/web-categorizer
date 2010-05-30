
#include "sql_exc.h"

#include "sql_api.h"
#include "../common/utils.h"

SqlException::SqlException(const char* msg){
    int l = strlen(msg) + 1;

    buffer = new char [l];

    memcpy(buffer, msg, sizeof(char) * l);
}

SqlException::SqlException(const char* msg, const SqlHandle* exc){
    // locals
    SQLSMALLINT cnt;

    SQLINTEGER  num;

    // query the number of diag records
    switch(sql_api.SQLGetDiagFieldW(*exc, *exc, 0, SQL_DIAG_NUMBER, &num, SQL_IS_INTEGER, &cnt)){
    case SQL_SUCCESS:
    //case SQL_SUCCESS_WITH_INFO:
        break;
    default:
        throw "SQLGetDiagField error (1)";
    }

    // message buffer
    string              out(msg);

    out.append(": ");

    for(int i = 1; i <= num; i++){
        SQLWCHAR        state[6] = {0, 0, 0, 0, 0, 0};
        SQLINTEGER      native;
        SQLWCHAR        buf3[1024];
        SQLSMALLINT     sz;

        switch(sql_api.SQLGetDiagRecW(exc, exc, i, state, &native, buf3, sizeof_a(buf3), &sz)){
        case SQL_SUCCESS:
        //case SQL_SUCCESS_WITH_INFO:
            break;
        default:
            throw "SQLGetDiagField error (2)";
        }

        basic_string<SQLWCHAR>  b_state(state);
        basic_string<SQLWCHAR>  b_buf(buf3);

        out.append("\n  ");
        out.append(b_state.begin(), b_state.end());
        out.append("  ");
        out.append(b_buf.begin(), b_buf.end());
    }

    int l = out.size() + 1;
    buffer = new char [l];
    std::copy(out.begin(), out.end(), buffer);

    buffer[l-1] = '\0';
}

~SqlException::SqlException(){
    delete [] buffer;
}


const char* SqlException::message() const {
    return buffer;
}


