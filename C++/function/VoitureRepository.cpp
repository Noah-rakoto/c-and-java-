#include "VoitureRepository.h"
#include <iostream>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

VoitureRepository::VoitureRepository(Connection& conn) : dbConn(conn) {}

std::vector<Voiture> VoitureRepository::getVoitures() {
    std::vector<Voiture> voitures;

    if (dbConn.con == nullptr || dbConn.con->isClosed()) {
        std::cerr << "Erreur : Pas de connexion active à la base de données." << std::endl;
        return voitures;
    }

    try {
        sql::Statement *stmt = dbConn.con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT nom, marque FROM Voiture");

        while (res->next()) {
            Voiture v;
            v.nom = res->getString("nom");
            v.marque = res->getString("marque");

            voitures.push_back(v);
        }

        delete res;
        delete stmt;

    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de la récupération des voitures : " << e.what() << std::endl;
    }

    return voitures;
}