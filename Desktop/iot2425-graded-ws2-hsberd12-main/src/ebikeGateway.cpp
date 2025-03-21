#include "web/WebServer.h"
#include <iostream>
#include <thread>
#include <arpa/inet.h>
#include <json/json.h>
#include <cstring>
#include <sstream>
#include <Poco/JSON/Array.h>
#include <Poco/JSON/Object.h>   // <== BU SATIRI EKLE


#define UDP_PORT 8080
#define WEB_SERVER_PORT 9831

void startUDPServer(Poco::JSON::Array::Ptr ebikes) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Error creating UDP socket!" << std::endl;
        return;
    }

    struct sockaddr_in serverAddr{}, clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(UDP_PORT);

    if (bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Binding failed!" << std::endl;
        return;
    }

    std::cout << "Socket Server waiting for messages on UDP port " << UDP_PORT << "..." << std::endl;

    char buffer[1024];
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddr, &clientLen);

        std::string jsonData(buffer);
        Json::CharReaderBuilder reader;
        Json::Value root;
        std::istringstream jsonStream(jsonData);
        std::string errors;

        if (Json::parseFromStream(reader, jsonStream, &root, &errors)) {
            Json::Value geoJSON;
            geoJSON["type"] = "Feature";
            geoJSON["geometry"]["type"] = "Point";
            geoJSON["geometry"]["coordinates"].append(root["longitude"].asFloat());
            geoJSON["geometry"]["coordinates"].append(root["latitude"].asFloat());
            geoJSON["properties"]["bike_id"] = root["bike_id"].asInt();
            geoJSON["properties"]["timestamp"] = root["timestamp"].asString();

            Poco::JSON::Object::Ptr feature = new Poco::JSON::Object();
            feature->set("type", "Feature");

            Poco::JSON::Object::Ptr geometry = new Poco::JSON::Object();
            geometry->set("type", "Point");

            Poco::JSON::Array::Ptr coords = new Poco::JSON::Array();
            coords->add(root["longitude"].asFloat());
            coords->add(root["latitude"].asFloat());
            geometry->set("coordinates", coords);

            feature->set("geometry", geometry);

            Poco::JSON::Object::Ptr properties = new Poco::JSON::Object();
            properties->set("bike_id", root["bike_id"].asInt());
            properties->set("timestamp", root["timestamp"].asString());
            feature->set("properties", properties);

            ebikes->add(feature);

            std::cout << "Processed GPS data: " << jsonData << std::endl;
            std::cout << "Total bikes received so far: " << ebikes->size() << std::endl;
        }

        // ACK
        std::string ack = "{\"status\": \"OK\"}";
        sendto(sockfd, ack.c_str(), ack.length(), 0, (struct sockaddr *)&clientAddr, clientLen);
    }
}

int main() {
    Poco::JSON::Array::Ptr ebikes = new Poco::JSON::Array();

    // UDP thread
    std::thread udpThread(startUDPServer, ebikes);
    udpThread.detach();

    try {
        WebServer webServer(ebikes);
        webServer.start(WEB_SERVER_PORT);

        // Keep main alive
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        return 0;
    } catch (const std::exception &ex) {
        std::cerr << "Server error: " << ex.what() << std::endl;
        return 1;
    }
}
