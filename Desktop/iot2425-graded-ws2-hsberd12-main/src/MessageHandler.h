#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <json/json.h>
#include <string>
#include <sstream>

class MessageHandler {
public:
    std::string parseMessage(const std::string& jsonStr) {
        Json::Value root;
        Json::CharReaderBuilder reader;
        std::string errors;
        std::istringstream s(jsonStr);

        if (!Json::parseFromStream(reader, s, &root, &errors)) {
            return "Invalid JSON: " + errors;
        }

        int ebike_id = root["ebike_id"].asInt();
        double latitude = root["gps"]["latitude"].asDouble(); 
        double longitude = root["gps"]["longitude"].asDouble(); 
        std::string timestamp = root["timestamp"].asString();

        Json::Value geoJson;
        geoJson["type"] = "Feature";
        geoJson["geometry"]["type"] = "Point";
        geoJson["geometry"]["coordinates"].append(longitude); 
        geoJson["geometry"]["coordinates"].append(latitude); 
        geoJson["properties"]["id"] = ebike_id;
        geoJson["properties"]["status"] = "unlocked";
        geoJson["properties"]["timestamp"] = timestamp;

        Json::StreamWriterBuilder writer;
        return Json::writeString(writer, geoJson);
    }
};

#endif

