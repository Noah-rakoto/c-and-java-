package Java.service;

import Java.Model.Voiture;

public class VoitureService {
    // function pour ecrire dans un txt
    public void ecrireVoitureDansFichier(Voiture voiture, String nomFichier) {
        try (java.io.FileWriter writer = new java.io.FileWriter(nomFichier, true)) {
            writer.write(voiture.getNom() + "," + voiture.getMarque() + "\n");
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
    }
}
