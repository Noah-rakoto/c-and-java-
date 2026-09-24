package com.cobra;

import org.omg.CORBA.*;
import java.io.*;
import CobraService.*;

public class Client {
    public static void main(String[] args) {
        try {
            // 1. Initialise l'ORB
            ORB orb = ORB.init(args, null);

            // 2. Lit le fichier IOR
            BufferedReader br = new BufferedReader(new FileReader("../C++/voiture.ior"));
            String ior = br.readLine();
            br.close();

            // 3. Obtient la référence de l'objet distant
            org.omg.CORBA.Object obj = orb.string_to_object(ior);
            VoitureService service = VoitureServiceHelper.narrow(obj);

            // 4. Appelle getVoitures et écrit dans un fichier
            Voiture[] voitures = service.getVoitures();
            FileWriter fw = new FileWriter("voitures.txt");
            for (Voiture v : voitures) {
                String ligne = "Nom: " + v.nom + ", Marque: " + v.marque + "\n";
                System.out.print(ligne);
                fw.write(ligne);
            }
            fw.close();
            System.out.println("\nDonnées écrites dans voitures.txt");

            // 5. Lit voitures.txt et envoie chaque voiture à C++ via CORBA pour insertion en base
            System.out.println("\nInsertion des voitures du fichier dans la base...");
            BufferedReader fichier = new BufferedReader(new FileReader("voitures.txt"));
            String ligne;
            while ((ligne = fichier.readLine()) != null) {
                String[] parties = ligne.replace("Nom: ", "").replace("Marque: ", "").split(", ");
                if (parties.length == 2) {
                    Voiture v = new Voiture(parties[0], parties[1]);
                    service.ajouterVoiture(v);
                    System.out.println("Inséré : " + v.nom + " - " + v.marque);
                }
            }
            fichier.close();
            System.out.println("Insertion terminée !");

        } catch (Exception e) {
            System.err.println("Erreur: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
