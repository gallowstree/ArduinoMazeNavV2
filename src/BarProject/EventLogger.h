#ifndef MYARDUINOPROJECT_EVENTLOGGER_H
#define MYARDUINOPROJECT_EVENTLOGGER_H

#include "Tile.h"
#include "TCPClient.h"
#include <Arduino.h>

class EventLogger {

    public:
        static void discoveredTile(Tile * tile);
        static void updateLocation(int facing, int row, int col);
        static void genericLog(float angle);
        static String host;
        static int port;

    private:
        static TCPClient client;

};

#endif 