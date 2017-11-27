#include "EventLogger.h"

String EventLogger::host = "UNDEFINED";
int EventLogger::port;
TCPClient EventLogger::client;

void EventLogger::discoveredTile(Tile * tile)
{
    
}

void EventLogger::updateLocation(int facing, int row, int col)
{
    String message = "LOC";
    message.concat("|");
    message.concat(row);
    message.concat(",");
    message.concat(col);
    message.concat("|");
    message.concat(facing);
    message.concat("|");
    Serial.print("Sending Message to ");
    Serial.println(EventLogger::host);
    
    if(!EventLogger::host.equals("UNDEFINED") && client.connect(const_cast<char*>(EventLogger::host.c_str()),EventLogger::port))
    {
        client.sendData(message);
    }

    client.close();
}

void EventLogger::genericLog(float angle)
{
    String message = "angle: ";
    message.concat(angle);
    if(!EventLogger::host.equals("UNDEFINED") && client.connect(const_cast<char*>(EventLogger::host.c_str()),EventLogger::port))
    {
        client.sendData(message);
    }

    client.close();
}


