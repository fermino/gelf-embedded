#ifndef GELF_UDPTRANSPORT_H
#define GELF_UDPTRANSPORT_H

#include "Transport.h"
#include "Message.h"

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define GRAYLOG_UDP_DEFAULT_PORT    12201

class UDPTransport : public Transport
{
public:
    explicit UDPTransport(char *host, int port = GRAYLOG_UDP_DEFAULT_PORT);
    void send(Message *message) override;
private:
    char *_host = nullptr;
    int _port = 0;

    WiFiUDP _udp = WiFiUDP();
};

#endif