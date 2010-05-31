
#include "sql_exc.h"

#include "sql_api.h"
#include "../web/utils.h"


#include <sstream>

SqlException::SqlException(const char* msg):
    buffer(0),
    codebuf(0),
    codenum(0)
{
    int l = strlen(msg) + 1;

    buffer = new char [l];

    memcpy(buffer, msg, sizeof(char) * l);
}

SqlException::SqlException(const char* msg, const SqlHandle* exc):
    buffer(0),
    codebuf(0),
    codenum(0)
{
    // locals
    SQLSMALLINT cnt;

    // query the number of diag records
    switch(SQLGetDiagFieldW(*exc, *exc, 0, SQL_DIAG_NUMBER, &codenum, SQL_IS_INTEGER, &cnt)){
    case SQL_SUCCESS:
    //case SQL_SUCCESS_WITH_INFO:
        break;
    default:
        throw "SQLGetDiagField error (1)";
    }

    // message buffer
    string              out(msg);

    out.append(": ");

    {
        ostringstream   oss;
        oss << "(" << codenum << ")";
        out.append(oss.str());
    }

    out.append("\n");

    // codebuf
    if(codenum > 0){
        codebuf = new char [codenum * 6];
    }

    for(int i = 1; i <= codenum; i++){
        SQLWCHAR        state[6] = {0, 0, 0, 0, 0, 0};
        SQLINTEGER      native;
        SQLWCHAR        buf3[1024];
        SQLSMALLINT     sz;

        switch(SQLGetDiagRecW(*exc, *exc, i, state, &native, buf3, sizeof_a(buf3), &sz)){
        case SQL_SUCCESS:
        //case SQL_SUCCESS_WITH_INFO:
            break;
        default:
            throw "SQLGetDiagField error (2)";
        }

        basic_string<SQLWCHAR>  b_state(state);
        basic_string<SQLWCHAR>  b_buf(buf3);

        out.append("  ");
        out.append(b_state.begin(), b_state.end());
        out.append("  ");
        out.append(b_buf.begin(), b_buf.end());
        out.append("\n");

        std::copy(state, state + 6, &codebuf[(i - 1) * 6]);
    }

    int l = out.size() + 1;
    buffer = new char [l];
    std::copy(out.begin(), out.end(), buffer);
    buffer[l-1] = '\0';
}

SqlException::SqlException(const SqlException& peer):
    buffer(0),
    codebuf(0),
    codenum(0)
{
    if(peer.buffer){
        int len = strlen(peer.buffer) + 1;
        buffer = new char [len];
        memcpy(buffer, peer.buffer, len);
    }

    if(peer.codebuf){
        codenum = peer.codenum;
        int len = codenum * 6;

        codebuf = new char [len];
        memcpy(codebuf, peer.codebuf, len);
    }
}

SqlException::~SqlException(){
    if(buffer) delete [] buffer;
    if(codebuf) delete [] codebuf;
}


const char* SqlException::message() const {
    return buffer;
}

const char* SqlException::operator [] (int i) const {
    if((i < 0) || (i >= codenum)) return 0;

    return &codebuf[i * 6];
}

