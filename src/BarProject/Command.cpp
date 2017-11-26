#include "Command.h"
#include "string.h"
#include <Arduino.h>


Command::Command():
    type(UNDEFINED),
    searchAlg(UNDEFINED) {}


void Command::parseCommand(String data) 
{

    if(data.startsWith("1"))
    {
        type = MAP_MAZE;
    }
    else if(data.startsWith("2"))
    {
        type = SEARCH;
        int firstSep = data.indexOf("|");
        int secSep = data.indexOf("|", firstSep+1);
        int thirdSep = data.indexOf("|", secSep+1);
        int fourthSep = data.indexOf("|", thirdSep+1);
        if (firstSep == -1 || secSep  == -1 || thirdSep  == -1 || fourthSep  == -1)
        {
            startTile = "NONE";
            goalTile = "NONE";
            searchAlg = UNDEFINED;
            return;
        }

        searchAlg = data.charAt(firstSep+1);
        startTile = data.substring(secSep+1,thirdSep);
        goalTile = data.substring(thirdSep+1,fourthSep);
    }
    else if(data.startsWith("4"))
    {
        type = SET_IP;
        int firstSep = data.indexOf("|");
        int secSep = data.indexOf("|", firstSep+1);
        if (firstSep == -1 || secSep  == -1 )
            serverIP = "UNDEFINED"; 
        else
            serverIP = data.substring(firstSep+1,secSep);
    }
    else
    {
        type = UNDEFINED;

    }
}