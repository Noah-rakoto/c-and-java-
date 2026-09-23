cd /home/victus/itu/S5/Prog/Cobra/C++
g++ -o serveur serveur.cpp function/Connection.cpp function/VoitureRepository.cpp ../VoitureServiceSK.cc \
    -I/usr/include/omniORB4 \
    -I/usr/include/mysql \
    -I.. \
    -lomniORB4 -lomnithread -lomniDynamic4 \
    -lmysqlcppconn \
    -std=c++17
