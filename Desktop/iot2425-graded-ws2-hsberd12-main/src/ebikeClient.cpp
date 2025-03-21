#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <arpa/inet.h>
#include <json/json.h>

#define SERVER_IP "127.0.0.1"

void sendGPSData(const std::string &filename, int port, int bikeId) {
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Failed to create socket!" << std::endl;
        return;
    }

    struct sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    serverAddr.sin_port = htons(port);

    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File couldn't open: " << filename << std::endl;
        return;
    }

    std::string line, bike_id, latitude, longitude, timestamp;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::getline(iss, bike_id, ',');    // <-- Eksik olan kısım
        std::getline(iss, latitude, ',');
        std::getline(iss, longitude, ',');
        std::getline(iss, timestamp, ',');

        try {
            Json::Value gpsData;
            gpsData["bike_id"] = bikeId;  // Komuttan gelen ID
            gpsData["timestamp"] = timestamp;
            gpsData["latitude"] = std::stof(latitude);
            gpsData["longitude"] = std::stof(longitude);

            Json::StreamWriterBuilder writer;
            std::string jsonData = Json::writeString(writer, gpsData);

            sendto(sockfd, jsonData.c_str(), jsonData.length(), 0,
                   (struct sockaddr*)&serverAddr, sizeof(serverAddr));

            std::cout << "Sent: " << jsonData << std::endl;

            char ackBuffer[1024] = {0};
            recv(sockfd, ackBuffer, sizeof(ackBuffer), 0);
            std::cout << "Ack received: " << ackBuffer << std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(1));
        } catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid data: " << ia.what() << " | line: " << line << std::endl;
        }
    }

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 4) { // program + csv + port + bike_id
        std::cerr << "Usage: " << argv[0] << " <csv_file> <port> <bike_id>" << std::endl;
        return 1;
    }

    std::string csvFile = argv[1];
    int port = std::stoi(argv[2]);
    int bikeId = std::stoi(argv[3]);

    sendGPSData(csvFile, port, bikeId);

    return 0;
}
