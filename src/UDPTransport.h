#ifndef GELF_UDPTRANSPORT_H
#define GELF_UDPTRANSPORT_H

#include "Transport.h"
#include "Message.h"

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <IPAddress.h>

#define GRAYLOG_UDP_DEFAULT_PORT    12201

class UDPTransport : public Transport
{
public:
    explicit UDPTransport(char *host, int port = GRAYLOG_UDP_DEFAULT_PORT);
    explicit UDPTransport(IPAddress ip_address, int port = GRAYLOG_UDP_DEFAULT_PORT);

    void send(Message *message) override;
private:
    char *_host = nullptr;
    IPAddress _ip_address;
    int _port = 0;

    WiFiUDP _udp = WiFiUDP();

    void beginPacket();
};

#endif