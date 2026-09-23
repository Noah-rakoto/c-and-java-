cd /home/victus/itu/S5/Prog/Cobra/Java
javac -cp "/home/victus/jacorb-libs/*:." CobraService/*.java Client.java
java -cp "/home/victus/jacorb-libs/*:." \
    -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB \
    -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton \
    Client
