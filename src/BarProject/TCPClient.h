#ifndef MYARDUINOPROJECT_TCPCLIENT_H
#define MYARDUINOPROJECT_TCPCLIENT_H

#include "SparkFunESP8266WiFi.h"
#include <Arduino.h>

class TCPClient {

    public:
        TCPClient();
        int connect(char * host, int port);
        void sendData(String data);
        void close();
        
    private:
        char * host;
        int port;               
        ESP8266Client client;
};

#endif 