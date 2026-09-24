mvn clean package
java -cp "target/voiture-client-1.0-SNAPSHOT-jar-with-dependencies.jar" \
    -Dorg.omg.CORBA.ORBClass=org.jacorb.orb.ORB \
    -Dorg.omg.CORBA.ORBSingletonClass=org.jacorb.orb.ORBSingleton \
    com.cobra.Client
