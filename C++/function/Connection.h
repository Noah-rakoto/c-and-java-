#ifndef CONNECTION_H
#define CONNECTION_H

#include <string>
#include <iostream>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/exception.h>
#include <mysql_driver.h>

struct Connection {
public:
    std::string namehote = "tcp://127.0.0.1:3306";
    std::string user = "root";
    std::string mdp = "";
    std::string nomBase = "corba_voiture";

    sql::Connection *con = nullptr;

    void connect();
    ~Connection();
};

#endif // CONNECTION_H