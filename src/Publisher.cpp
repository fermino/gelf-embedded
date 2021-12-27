#include "../include/Publisher.h"

Publisher::Publisher(Transport *transport) {
    _transport = transport;
}

void Publisher::publish(Message *message) {
    _transport->send(message);
}
