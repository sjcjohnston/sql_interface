#include <iostream>

#include <windows.h>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;


#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

void dbConstruction();

//Specify required SQL handles
RETCODE rc;         //ODBC return code
SQLHENV henv;       //environment handle
SQLHDBC hdbc;       //database connection handle
SQLHSTMT hstmt;     //statement handle
SDWORD cbData;      //Output length of data (not sure what the purpose of this is)
UCHAR errmsg[100];

int main()
{
//    const int MAX_CHAR = 1024;



    char dbName[] = "fcrb"; //name of the database
    char decision;

    do
    {
        cout << "Open database " << dbName << "? " << endl;
        cin >> decision;
    } while (cin.fail());

    if (decision == 'y')
    {
        cout << "Attempting to open database " << dbName << "..." << endl;
        SQLAllocEnv(&henv);
        rc = SQLAllocConnect(henv, &hdbc);
        rc = SQLConnect(hdbc, (unsigned char*)dbName, SQL_NTS, 0, 0, 0, 0);
    }
    else
    {
        do
        {
            cout << "Specify additional database. " << endl;
            cin >> dbName;
        } while (cin.fail());

        cout << "Attempting to open database " << dbName << "..." << endl;
        SQLAllocEnv(&henv);
        rc = SQLAllocConnect(henv, &hdbc);
        rc = SQLConnect(hdbc, (unsigned char*)dbName, SQL_NTS, 0, 0, 0, 0);
    }

    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
    {
        cout << "Cannot open database -- ensure ODBC is configured properly" << endl;
        cout << rc << endl;
        SQLError( henv, hdbc, SQL_NULL_HSTMT, NULL, NULL, errmsg, sizeof(errmsg), NULL );
        cout << errmsg << endl;
    }
    else
    {
        cout << "Database successfully opened." << endl;
    }
    int q;
    while (true)
    {
        int option;
        cout << "What would you like to do?\n\t1-Modify Database Structure\n\t2-Create a new case\n\t3-Update a case\n\t4-Exit the program\n\nEnter a number: " << endl;
        cin >> option;
        switch(option)
        {
        case 1:
            dbConstruction();
        case 2:
            q = 2;
        case 3:
            q = 3;
        case 4:
            break;
        default:
            continue;
        }
    }

    return 0;
}

void dbConstruction()
{
    while (true)
    {
        char command[1024];
        cout << "Enter an SQL command. Else enter: 'exit'" << endl;
        cin.getline(command, 1024);
        if (strcmp(command,'exit') == 0)
        {
            break;
        }
        else
        {
            SQLAllocStmt(hdbc, &hstmt);
//            char* sql = "CREATE TABLE Cases (CaseID integer, MotherName text);";
            cout << "Executing Command..." << endl;
            rc = SQLExecDirect(hstmt, (unsigned char *)command, SQL_NTS);
            if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
            {
                cout << "Execution Unsuccessful." << endl;
                SQLError( henv, hdbc, SQL_NULL_HSTMT, NULL, NULL, errmsg, sizeof(errmsg), NULL );
                cout << "Error: " << errmsg << endl;
                cout << rc << endl;
            }
            else
            {
                cout << "Execution Successful.";
            }
        }

    }
}
//
////    }
////
//    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO))
//    {
//        cout << "Cannot open database -- ensure ODBC is configured properly" << endl;
//        SQLError( henv, hdbc, SQL_NULL_HSTMT, NULL, NULL, errmsg, sizeof(errmsg), NULL );
//        cout << errmsg << endl;
//        cout << rc << endl;
//    }
//    if (rc == SQL_INVALID_HANDLE)
//    {
//        cout << "Invalid Handle" << endl;
//    }

