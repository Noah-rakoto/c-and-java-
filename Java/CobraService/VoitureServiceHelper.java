package CobraService;

public abstract class VoitureServiceHelper {
    public static VoitureService narrow(org.omg.CORBA.Object obj) {
        if (obj == null)
            return null;
        else if (obj instanceof VoitureService)
            return (VoitureService) obj;
        else if (!obj._is_a(id()))
            throw new org.omg.CORBA.BAD_PARAM();
        else {
            org.omg.CORBA.portable.Delegate delegate = ((org.omg.CORBA.portable.ObjectImpl) obj)._get_delegate();
            _VoitureServiceStub stub = new _VoitureServiceStub();
            stub._set_delegate(delegate);
            return stub;
        }
    }
    
    public static String id() {
        return "IDL:CobraService/VoitureService:1.0";
    }
}
