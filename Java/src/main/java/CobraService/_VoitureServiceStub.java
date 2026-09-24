package CobraService;

public class _VoitureServiceStub extends org.omg.CORBA.portable.ObjectImpl implements VoitureService {

    public Voiture[] getVoitures() {
        org.omg.CORBA.portable.InputStream in = null;
        try {
            org.omg.CORBA.portable.OutputStream out = _request("getVoitures", true);
            in = _invoke(out);
            int length = in.read_ulong();
            Voiture[] result = new Voiture[length];
            for (int i = 0; i < length; i++) {
                result[i] = new Voiture();
                result[i].nom = in.read_string();
                result[i].marque = in.read_string();
            }
            return result;
        } catch (org.omg.CORBA.portable.ApplicationException ex) {
            in = ex.getInputStream();
            throw new org.omg.CORBA.MARSHAL(ex.getId());
        } catch (org.omg.CORBA.portable.RemarshalException ex) {
            return getVoitures();
        } finally {
            _releaseReply(in);
        }
    }

    public void ajouterVoiture(Voiture v) {
        org.omg.CORBA.portable.InputStream in = null;
        try {
            org.omg.CORBA.portable.OutputStream out = _request("ajouterVoiture", true);
            // Envoie la voiture au serveur C++
            out.write_string(v.nom);
            out.write_string(v.marque);
            in = _invoke(out);
        } catch (org.omg.CORBA.portable.ApplicationException ex) {
            in = ex.getInputStream();
            throw new org.omg.CORBA.MARSHAL(ex.getId());
        } catch (org.omg.CORBA.portable.RemarshalException ex) {
            ajouterVoiture(v);
        } finally {
            _releaseReply(in);
        }
    }

    public void lireVoituresDepuisFichier(String nomFichier) {
        org.omg.CORBA.portable.InputStream in = null;
        try {
            org.omg.CORBA.portable.OutputStream out = _request("lireVoituresDepuisFichier", true);
            out.write_string(nomFichier);
            in = _invoke(out);
        } catch (org.omg.CORBA.portable.ApplicationException ex) {
            in = ex.getInputStream();
            throw new org.omg.CORBA.MARSHAL(ex.getId());
        } catch (org.omg.CORBA.portable.RemarshalException ex) {
            lireVoituresDepuisFichier(nomFichier);
        } finally {
            _releaseReply(in);
        }
    }

    public String[] _ids() {
        return new String[] { "IDL:CobraService/VoitureService:1.0" };
    }
}
