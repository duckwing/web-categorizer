
#ifndef __SQL_EXC_H__
#define __SQL_EXC_H__

//////////////////////////////
// exceptions
//


class SqlException {
private:
    SQLCHAR     *buffer;
public:
    SqlException(const char* msg){
        int l = strlen(msg) + 1;

        buffer = new SQLCHAR [l];

        memcpy(buffer, msg, sizeof(SQLCHAR) * l);
    }

    SqlException(const char* msg, const SqlHandle& exc){
        // locals
        SQLSMALLINT cnt;

        SQLINTEGER  num;

        // query the number of diag records
        switch(sapi.SQLGetDiagFieldW(exc, exc, 0, SQL_DIAG_NUMBER, &num, SQL_IS_INTEGER, &cnt)){
        case SQL_SUCCESS:
        //case SQL_SUCCESS_WITH_INFO:
            break;
        default:
            throw "SQLGetDiagField error (1)";
        }

        basic_string<SQLCHAR>       buf1;
        basic_string<SQLWCHAR>      buf2;

        for(int i = 1; i <= num; i++){
            SQLWCHAR        state[6] = {0, 0, 0, 0, 0, 0};
            SQLINTEGER      native;
            SQLWCHAR        buf3[1024];
            SQLSMALLINT     sz;

            switch(sapi.SQLGetDiagRecW(exc, exc, i, state, &native, buf3, sizeof_a(buf3), &sz)){
            case SQL_SUCCESS:
            //case SQL_SUCCESS_WITH_INFO:
                break;
            default:
                throw "SQLGetDiagField error (2)";
            }

            basic_string<SQLWCHAR>  b_state(state);
            basic_string<SQLWCHAR>  b_buf(buf3);

            buf2.append(L"\n  ");
            buf2.append(b_state);
            buf2.append(L"  ");
            buf2.append(b_buf);
        }

        string      m(msg);
        m.append(": ");

        buf1.append(m.begin(), m.end());
        buf1.append(buf2.begin(), buf2.end());

        int l = buf1.size() + 1;
        buffer = new SQLCHAR [l];
        std::copy(buf1.begin(), buf1.end(), buffer);

        buffer[l-1] = '\0';
    }

    SQLCHAR* message() const {
        return buffer;
    }

    ~SqlException(){
        delete [] buffer;
    }
};

#endif // __SQL_EXC_H__

