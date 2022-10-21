#ifndef GELF_MESSAGE_H
#define GELF_MESSAGE_H

// TODO add consts where needed!

#include "ArduinoJson.h"
// TODO: different amounts of memory depending on the platform!

#ifdef ESP8266
    #include <ESP8266WiFi.h>
    #define _GELF_HOST (WiFi.hostname())
#elif defined(ESP32)
    #include <WiFi.h>
    #define _GELF_HOST (WiFi.getHostname())
#else
    #define _GELF_HOST ("graylog-default-host")
#endif

class Message
{
public:
    explicit Message(const char *short_message) {
        reset(short_message);
    }
    void reset(const char *short_message) {
        _json = StaticJsonDocument<512>();
        _json["version"] = "1.1";
        _json["host"] = _GELF_HOST;
        _json["short_message"] = short_message;
    }

    template<typename T>
    void set(const char *field, const T value) {
        if (strncmp("id", field, 2) == 0 || strncmp("_id", field, 3) == 0) {
            return;
        }

        // As defined in the documentation, additional fields should be prefixed with an underscore
        // In practice graylog takes any other field as an additional field so it's not strictly necessary
        /*if (field[0] != '_') {
            // TODO: prepend underscore!
        }*/

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