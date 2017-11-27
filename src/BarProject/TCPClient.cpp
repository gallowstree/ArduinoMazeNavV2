#include "TCPClient.h"

TCPClient::TCPClient(){}

int TCPClient::connect(char * host, int port)
{
    return client.connect(host,port);
}

void TCPClient::sendData(String data)
{
    client.print(data);
}

void TCPClient::close()
{
    client.stop();
}