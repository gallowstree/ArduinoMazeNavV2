#ifndef MYARDUINOPROJECT_TCPSERVER_H
#define MYARDUINOPROJECT_TCPSERVER_H

#include "SparkFunESP8266WiFi.h"
#include "Command.h"

class TCPServer {

    public:
        TCPServer(int port, Command * command);
        void begin();
        void wait4Command();

    private:
        int port;               
        ESP8266Server server;
        char inBuffer[127];    
        Command * command;
};

#endif 