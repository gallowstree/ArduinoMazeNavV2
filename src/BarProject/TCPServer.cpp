#include "TCPServer.h"
#include <Arduino.h>


TCPServer::TCPServer(int port, Command * command):
    port(port),
    command(command),
    server(ESP8266Server(port)) {}

void TCPServer::begin() {
    this->server.begin();
}

void TCPServer::wait4Command() {
    ESP8266Client client = server.available(100);
    if (client) 
    {
        Serial.println(F("Client Connected!"));
        int i = 0;
        bool shouldCopy = false;
        memset(inBuffer, 0, sizeof(inBuffer));
        while (client.connected()) 
        {
            while (!client.available());
            
            char c = client.read();
            if (shouldCopy)
                inBuffer[i++] = c;
            if (!shouldCopy && c == ':')
                shouldCopy = true;                
        }
        Serial.println("inBuffer:");
        Serial.println(inBuffer);
        command->parseCommand(String(inBuffer));
    }   

}