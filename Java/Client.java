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

            // 4. Appelle la méthode distante
            Voiture[] voitures = service.getVoitures();

            // 5. Écrit dans un fichier
            FileWriter fw = new FileWriter("voitures.txt");
            for (Voiture v : voitures) {
                String ligne = "Nom: " + v.nom + ", Marque: " + v.marque + "\n";
                System.out.print(ligne);
                fw.write(ligne);
            }
            fw.close();

            System.out.println("\nDonnées écrites dans voitures.txt");

        } catch (Exception e) {
            System.err.println("Erreur: " + e.getMessage());
            e.printStackTrace();
        }
    }
}
