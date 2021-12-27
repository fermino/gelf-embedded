#ifndef GELF_PUBLISHER_H
#define GELF_PUBLISHER_H

#include "Transport.h"
#include "Message.h"

class Publisher
{
public:
    explicit Publisher(Transport *transport);
    void publish(Message *message);
private:
    Transport *_transport = nullptr;
};

#endif