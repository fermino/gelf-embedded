#include "UDPTransport.h"

UDPTransport::UDPTransport(char *host, int port)
{
    _host = host;
    _port = port;
}

void UDPTransport::send(Message *message)
{
    _udp.beginPacket(_host, _port);

    unsigned long length = message->getEncodedLength();
    char buffer[length + 1];
    message->encode(buffer, length); // Debería ser length + 1??
    buffer[length] = '\0'; // This might be unnecessary

    _udp.write(buffer);
    _udp.endPacket();

    // https://stackoverflow.com/questions/1098897/what-is-the-largest-safe-udp-packet-size-on-the-internet
    // PS: We don't want to deal with chunking yet
    //udp.begin(_port);
}