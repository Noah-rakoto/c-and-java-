#include "VoitureService.hh"
#include "function/VoitureRepository.h"
#include "function/Connection.h"
#include <iostream>
#include <fstream>

// Implémentation du service CORBA
class VoitureService_impl : public POA_CobraService::VoitureService {
public:
    VoitureService_impl(VoitureRepository* repo) : repository(repo) {}
    
    CobraService::VoitureList* getVoitures() {
        // Récupère les voitures depuis la base
        std::vector<Voiture> voitures = repository->getVoitures();
        
        // Crée la séquence CORBA
        CobraService::VoitureList* liste = new CobraService::VoitureList();
        liste->length(voitures.size());
        
        for (size_t i = 0; i < voitures.size(); i++) {
            (*liste)[i].nom = CORBA::string_dup(voitures[i].nom.c_str());
            (*liste)[i].marque = CORBA::string_dup(voitures[i].marque.c_str());
        }
        
        return liste;
    }
    void ajouterVoiture(const CobraService::Voiture& v) {
        repository->ajouterVoiture(v.nom.in(), v.marque.in());
    }

    void lireVoituresDepuisFichier(const char* nomFichier) {
        std::ifstream fichier(nomFichier);
        std::string ligne;

        while (std::getline(fichier, ligne)) {
            // format attendu depuis Java: "Nom: xxx, Marque: yyy"
            size_t posNom = ligne.find("Nom: ");
            size_t posMarque = ligne.find(", Marque: ");
            if (posNom != std::string::npos && posMarque != std::string::npos) {
                std::string nom = ligne.substr(5, posMarque - 5);
                std::string marque = ligne.substr(posMarque + 10);
                repository->ajouterVoiture(nom, marque);
                std::cout << "Inséré depuis fichier : " << nom << ", " << marque << std::endl;
            }
        }
    }

    

private:
    VoitureRepository* repository;
};

int main(int argc, char** argv) {
    try {
        // 1. Connexion à la base
        Connection conn;
        conn.connect();
        VoitureRepository repo(conn);
        
        // 2. Initialise l'ORB avec endpoint sur 127.0.0.1
        const char* orbArgs[] = { "serveur", "-ORBendPoint", "giop:tcp:127.0.0.1:" };
        int orbArgc = 3;
        CORBA::ORB_var orb = CORBA::ORB_init(orbArgc, const_cast<char**>(orbArgs));
        
        // 3. Obtient le POA
        CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
        PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
        
        // 4. Active le POA manager
        PortableServer::POAManager_var pman = poa->the_POAManager();
        pman->activate();
        
        // 5. Crée le servant
        VoitureService_impl* service = new VoitureService_impl(&repo);
        
        // 6. Active l'objet
        PortableServer::ObjectId_var oid = poa->activate_object(service);
        CORBA::Object_var ref = poa->id_to_reference(oid);
        
        // 7. Écrit l'IOR dans un fichier
        CORBA::String_var ior = orb->object_to_string(ref);
        std::ofstream iorFile("voiture.ior");
        iorFile << ior << std::endl;
        iorFile.close();
        
        std::cout << "Serveur CORBA prêt. IOR écrit dans voiture.ior" << std::endl;
        
        // 8. Attend les requêtes
        orb->run();
        
        // Cleanup
        service->_remove_ref();
        orb->destroy();
        
    } catch (CORBA::Exception& e) {
        std::cerr << "Erreur CORBA: " << e._name() << std::endl;
        return 1;
    }
    
    return 0;
}
