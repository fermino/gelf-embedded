#ifndef GELF_MESSAGE_H
#define GELF_MESSAGE_H

// TODO add consts where needed!

#include "ArduinoJson.h"
// TODO: different amounts of memory depending on the platform!

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#define GRAYLOG_DEFAULT_HOST "graylog-default-host"

class Message
{
public:
    explicit Message(const char *short_message) {

        _json["version"] = "1.1";
#ifdef ESP8266
        _json["host"] = WiFi.hostname();
#else
        _json["host"] = GRAYLOG_DEFAULT_HOST;
#endif
        _json["short_message"] = short_message;
    }
    template<typename T>
    void set(const char *field, T value) {
        if (strncmp("id", field, 2) == 0 || strncmp("_id", field, 3) == 0) {
            return;
        }

        if (field[0] != '_') {
            // TODO: prepend underscore!
        }

        // TODO: Check regex - ^[\w\.\-]*$

        _json[field] = value;
    }

    unsigned int getEncodedLength() {
        return measureJson(_json);
    }
    void encode(char *buffer, size_t buffer_size) {
        serializeJson(_json, buffer, buffer_size);
    }

private:
    // We could use the heap but whatever
    StaticJsonDocument<512> _json;
};

#endif