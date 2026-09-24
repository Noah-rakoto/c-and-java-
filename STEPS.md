# CORBA C++ ↔ Java - Étapes

---

## C++ Serveur → Java Client (C++ lit SQL, Java reçoit)

### 1. Créer le fichier IDL
Définir l'interface commune dans `VoitureService.idl` :
- La struct `Voiture` (nom, marque)
- Le typedef `VoitureList` (sequence de Voiture)
- L'interface avec les fonctions : `getVoitures()`, `ajouterVoiture()`, `lireVoituresDepuisFichier()`

### 2. Compiler l'IDL côté C++
```bash
omniidl -bcxx VoitureService.idl
```
Génère : `VoitureService.hh` et `VoitureServiceSK.cc`

### 3. Créer le serveur C++
Dans `serveur.cpp` :
- Créer une classe `VoitureService_impl` qui hérite de `POA_CobraService::VoitureService`
- Implémenter toutes les fonctions de l'IDL
- Initialiser l'ORB avec `giop:tcp:127.0.0.1:`
- Écrire l'IOR dans `voiture.ior`
- Appeler `orb->run()`

### 4. Créer VoitureRepository C++
Dans `function/VoitureRepository.h` et `.cpp` :
- `getVoitures()` : SELECT dans la base
- `ajouterVoiture(nom, marque)` : INSERT dans la base
- Inclure `<cppconn/prepared_statement.h>`

### 5. Compiler le serveur C++
```bash
g++ -o serveur serveur.cpp function/Connection.cpp function/VoitureRepository.cpp ../VoitureServiceSK.cc \
    -I/usr/include/omniORB4 -I/usr/include/mysql -I.. \
    -lomniORB4 -lomnithread -lmysqlcppconn -std=c++17
```

### 6. Créer les classes Java manuellement (Java 21 n'a plus idlj)
Dans `src/main/java/CobraService/` :
- `Voiture.java` : la struct
- `VoitureService.java` : l'interface
- `VoitureServiceHelper.java` : le narrow
- `_VoitureServiceStub.java` : le stub (sérialisation/désérialisation)

### 7. Créer le client Java
Dans `src/main/java/com/cobra/Client.java` :
- Initialiser l'ORB JacORB
- Lire `voiture.ior`
- Appeler `VoitureServiceHelper.narrow()`
- Appeler les fonctions distantes

### 8. Configurer Maven (pom.xml)
Dépendances :
- `jacorb-omgapi:3.9`
- `jacorb:3.9`
- `jboss-rmi-api_1.0_spec:1.0.6.Final`
- `slf4j-api:1.7.30`
- `slf4j-simple:1.7.30`

### 9. Compiler et lancer
```bash
# Compiler Java
mvn clean package

# Lancer le serveur C++ (terminal 1)
./serveur

# Lancer le client Java (terminal 2)
java -cp "target/voiture-client-1.0-SNAPSHOT-jar-with-dependencies.jar" \
    -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB \
    -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton \
    com.cobra.Client
```

---

## Java Client → C++ Serveur (Java envoie, C++ insère en SQL)

### 1. Modifier l'IDL
Ajouter les fonctions d'écriture dans l'interface :
```idl
void ajouterVoiture(in Voiture v);
void lireVoituresDepuisFichier(in string nomFichier);
```

### 2. Recompiler l'IDL
```bash
omniidl -bcxx VoitureService.idl
```

### 3. Implémenter côté C++ (serveur reçoit)
Dans `serveur.cpp` :
- `ajouterVoiture()` : appelle `repository->ajouterVoiture()`
- `lireVoituresDepuisFichier()` : lit le fichier ligne par ligne et insère chaque voiture

### 4. Implémenter côté Java (client envoie)
Dans `_VoitureServiceStub.java` :
- `ajouterVoiture()` : sérialise `nom` et `marque` avec `write_string()`
- `lireVoituresDepuisFichier()` : envoie le nom du fichier avec `write_string()`

Dans `Client.java` :
- Lire `voitures.txt`
- Appeler `service.ajouterVoiture()` pour chaque ligne
- Ou appeler `service.lireVoituresDepuisFichier("voitures.txt")`

### 5. Recompiler et relancer
```bash
# C++
g++ -o serveur serveur.cpp function/Connection.cpp function/VoitureRepository.cpp ../VoitureServiceSK.cc \
    -I/usr/include/omniORB4 -I/usr/include/mysql -I.. \
    -lomniORB4 -lomnithread -lmysqlcppconn -std=c++17

# Java
mvn clean package
```

---

## Résumé du flux complet

```
Java (Client.java)
    ↓ getVoitures() via CORBA
C++ (serveur.cpp)
    ↓ SELECT
Base SQL (corba_voiture)
    ↓ résultat
C++ → Java
    ↓ écrit
voitures.txt
    ↓ ajouterVoiture() via CORBA
C++ (serveur.cpp)
    ↓ INSERT
Base SQL (corba_voiture)
```
