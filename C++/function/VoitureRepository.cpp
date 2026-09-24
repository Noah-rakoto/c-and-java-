#include "VoitureRepository.h"
#include <iostream>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

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

void VoitureRepository::ajouterVoiture(const std::string& nom, const std::string& marque) {
    if (dbConn.con == nullptr || dbConn.con->isClosed()) {
        std::cerr << "Erreur : Pas de connexion active à la base de données." << std::endl;
        return;
    }

    try {
        sql::PreparedStatement *pstmt = dbConn.con->prepareStatement(
            "INSERT INTO Voiture (nom, marque) VALUES (?, ?)"
        );
        pstmt->setString(1, nom);
        pstmt->setString(2, marque);
        pstmt->execute();
        delete pstmt;
        std::cout << "Voiture ajoutée : " << nom << ", " << marque << std::endl;
    } catch (sql::SQLException &e) {
        std::cerr << "Erreur lors de l'ajout : " << e.what() << std::endl;
    }
}
