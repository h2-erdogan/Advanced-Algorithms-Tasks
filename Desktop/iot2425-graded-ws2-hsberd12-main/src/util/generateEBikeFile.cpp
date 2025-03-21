#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <iomanip>
#include <ctime>

// Constants
const double LAT_MIN = 51.45;
const double LAT_MAX = 51.46;
const double LON_MIN = -2.6;
const double LON_MAX = -2.5;
const std::string FILE_PREFIX = "data/sim-eBike-";
const double VARIATION = 0.0001;

// Function to generate a random coordinate within a given range
double randomCoord(double min, double max, std::mt19937& gen) {
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

// Function to slightly change the coordinates to simulate movement
void varyCoord(double& lat, double& lon, std::mt19937& gen) {
    std::uniform_real_distribution<> dis(-VARIATION, VARIATION);
    lat += dis(gen);
    lon += dis(gen);
}

// Function to generate a timestamp (ISO 8601 format)
std::string generateTimestamp(int index) {
    std::time_t now = std::time(nullptr);
    now += index * 60; 
    std::tm* gmt = std::gmtime(&now);
    char buffer[30];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", gmt);
    return std::string(buffer);
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <seed> <num_files> <num_rows>" << std::endl;
        return 1;
    }

    int seed = std::stoi(argv[1]);
    int numFiles = std::stoi(argv[2]);
    int numRows = std::stoi(argv[3]);

    std::mt19937 gen(seed);

    for (int fileIndex = 0; fileIndex < numFiles; ++fileIndex) {
        std::string fileName = FILE_PREFIX + std::to_string(fileIndex + 1) + ".csv";
        std::ofstream outFile(fileName);

        if (!outFile.is_open()) {
            std::cerr << "Failed to open file: " << fileName << std::endl;
            return 1;
        }

        outFile << "ebike_id,latitude,longitude,timestamp\n";

        double lat = randomCoord(LAT_MIN, LAT_MAX, gen);
        double lon = randomCoord(LON_MIN, LON_MAX, gen);

        for (int rowIndex = 0; rowIndex < numRows; ++rowIndex) {
            std::string timestamp = generateTimestamp(rowIndex);
            outFile << (fileIndex + 1) << "," << std::fixed << std::setprecision(6) << lat << "," << lon << "," << timestamp << "\n";
            varyCoord(lat, lon, gen);
        }

        outFile.close();
    }

    return 0;
}
