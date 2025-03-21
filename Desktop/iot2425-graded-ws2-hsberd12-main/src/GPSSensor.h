#ifndef GPSSENSOR_H
#define GPSSENSOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime> 

class GPSSensor {
private:
    std::vector<std::string> gpsData;
    std::size_t currentIndex;

public:
    GPSSensor(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        currentIndex = 0;

        if (!file) {
            std::cerr << "Error: Could not open file " << filename << std::endl;
            return;
        }

        while (std::getline(file, line)) {
            if (line.find(",") != std::string::npos) {
                for (char &c : line) {
                    if (c == ',') c = ';'; 
                }
            } else {
                std::cerr << "Warning: GPS data is not in expected format in " << filename << std::endl;
            }
            gpsData.push_back(line);
        }
        file.close();
    }

    std::string getGPSData() {
        if (currentIndex < gpsData.size()) {
            return gpsData[currentIndex++];
        }
        return "No more data";
    }

    std::string getGPSDataJSON(int ebike_id) {
        if (currentIndex < gpsData.size()) {
            std::string gps = gpsData[currentIndex++];
            size_t sep = gps.find(';');
            std::string lat = gps.substr(0, sep);
            std::string lon = gps.substr(sep + 1);

            time_t now = time(0);
            char timestamp[20];
            strftime(timestamp, sizeof(timestamp), "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));

            std::stringstream json;
            json << "{"
                 << "\"ebike_id\":" << ebike_id << ","
                 << "\"timestamp\":\"" << timestamp << "\","
                 << "\"gps\":{"
                 << "\"latitude\":" << lat << ","
                 << "\"longitude\":" << lon
                 << "}}";
            return json.str();
        }
        return "{}";
    }
};

#endif
