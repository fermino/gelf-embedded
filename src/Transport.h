#ifndef GELF_TRANSPORT_H
#define GELF_TRANSPORT_H

#include "Message.h"

class Transport
{
public:
    virtual void send(Message *message) = 0;
};

#endif