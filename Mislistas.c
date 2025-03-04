#include <stdio.h>
#include <sql.h>
#include <sqlext.h>

// Definir la conexión
#define SERVER "localhost"
#define DATABASE "JuegoDB"
#define USERNAME "tu_usuario"
#define PASSWORD "tu_contraseña"

void consultaJugadores() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLHSTMT hStmt;
    SQLRETURN ret;

    // Conectar con el servidor SQL Server
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    ret = SQLConnect(hDbc, (SQLCHAR *)SERVER, SQL_NTS, (SQLCHAR *)USERNAME, SQL_NTS, (SQLCHAR *)PASSWORD, SQL_NTS);

    if (ret != SQL_SUCCESS && ret != SQL_SUCCESS_WITH_INFO) {
        printf("Error al conectar a la base de datos\n");
        return;
    }

    // Crear la consulta
    SQLCHAR query[] = "SELECT Nombre, NumeroPartidas FROM Jugador WHERE NumeroPartidas > 10";
    ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    ret = SQLExecDirect(hStmt, query, SQL_NTS);

    // Mostrar resultados de la consulta
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        SQLCHAR nombre[50];
        SQLINTEGER numPartidas;

        while (SQLFetch(hStmt) == SQL_SUCCESS) {
            SQLGetData(hStmt, 1, SQL_C_CHAR, nombre, sizeof(nombre), NULL);
            SQLGetData(hStmt, 2, SQL_C_LONG, &numPartidas, 0, NULL);
            printf("Nombre: %s, Número de Partidas: %d\n", nombre, numPartidas);
        }
    } else {
        printf("Error en la consulta\n");
    }

    // Liberar los manejadores
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}

int main() {
    consultaJugadores();
    return 0;
}
