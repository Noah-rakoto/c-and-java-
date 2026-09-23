#ifndef VOITURE_REPOSITORY_H
#define VOITURE_REPOSITORY_H

#include <vector>
#include "Voiture.h"
#include "Connection.h"

class VoitureRepository {
private:
    Connection& dbConn;

public:
    VoitureRepository(Connection& conn);
    std::vector<Voiture> getVoitures();
};

#endif // VOITURE_REPOSITORY_H