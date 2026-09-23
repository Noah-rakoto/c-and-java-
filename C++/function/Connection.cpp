#include "Connection.h"

void Connection::connect() {
    try {
        sql::mysql::MySQL_Driver *driver = sql::mysql::get_driver_instance();
        con = driver->connect(namehote, user, mdp);
        con->setSchema(nomBase);
        std::cout << "Connexion réussie à la base de données !" << std::endl;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur de connexion : " << e.what() << std::endl;
    }
}

Connection::~Connection() {
    if (con != nullptr) {
        delete con;
    }
}