
# eBike Fleet Monitoring System 🚲🌍

## Project Overview

This project simulates an **eBike Fleet Monitoring System** using IoT concepts. It allows monitoring of multiple eBikes' locations and statuses in real-time. It includes:

- UDP communication between eBike clients and a Gateway.
- JSON formatted GPS data transfer.
- A Web Server to display bike locations on a map (using Leaflet.js) and in a table format.

## Project Structure

```
├── src
│   ├── ebikeClient.cpp             # eBike client sending GPS data
│   ├── ebikeGateway.cpp            # UDP server gateway
│   ├── web
│   │   ├── EbikeHandler.cpp        # Handles JSON response to client
│   │   ├── FileHandler.cpp         # Serves static HTML files
│   │   ├── RequestHandlerFactory.cpp # Handles incoming HTTP requests
│   │   ├── WebServer.cpp           # Starts web server
│   ├── util
│   │   └── generateEBikeFile.cpp   # Optional: Generates bike data file
│
├── data
│   ├── sim-eBike-1.csv
│   ├── sim-eBike-2.csv
│   ├── sim-eBike-3.csv
│   └── sim-eBike-4.csv             # Simulated GPS data for each bike
│
├── html
│   └── map.html                    # Web interface to display map & table
├── Makefile
└── README.md
```

## Dependencies

- **C++17**
- **POCO libraries**
    - PocoNet
    - PocoJSON
- **jsoncpp**
- **Leaflet.js** (for map UI)
- Tested on **macOS (M1/M2)** using **Homebrew**

## Installation & Setup

### Install dependencies (macOS)
```bash
brew install poco jsoncpp
```

## Building the Project

```bash
make clean
make
```

## Running the Components

### 1. Start the Gateway Server:

```bash
./ebikeGateway
```

- Listens on **UDP port 8080**.
- Starts HTTP server on **http://localhost:9831**.
- Sends JSON response of all eBikes.

### 2. Start eBike Clients:

Each eBike client simulates GPS data by reading from CSV:

```bash
./ebikeClient data/sim-eBike-1.csv 8080 1
./ebikeClient data/sim-eBike-2.csv 8080 2
./ebikeClient data/sim-eBike-3.csv 8080 3
./ebikeClient data/sim-eBike-4.csv 8080 4
```

> **Arguments:**
> 1. CSV file path
> 2. UDP port
> 3. eBike ID

## Viewing the Web Interface 🌍

Open your browser:

```
http://localhost:9831/map.html
```

- Map will show real-time locations.
- Table lists:
  - Bike ID
  - Coordinates
  - Status
  - Last Updated Timestamp

## Key Features

- **UDP Communication:** eBike clients continuously send their location data.
- **JSON Data Format:** Lightweight and easy to parse.
- **Web Server:** Serves both data and HTML content.
- **Dynamic Frontend:**
  - Leaflet.js displays markers for bikes.
  - Table updates in real-time.

## Technologies Used

| Component              | Technology                           |
|-----------------------|--------------------------------------|
| Communication         | UDP Sockets                          |
| Data Format           | JSON (POCO & jsoncpp)                |
| Web Server            | POCO Net HTTP Server                 |
| Frontend              | HTML, CSS, JavaScript, Leaflet.js    |
| Build Tool            | Makefile                             |
| Language              | C++ (C++17 Standard)                 |

## Troubleshooting

- **Port Issues:** Make sure **port 8080** (UDP) and **9831 (HTTP)** are free.
- **Dependencies:** Ensure POCO and jsoncpp are installed correctly.
- **Multiple Clients:** You can open separate terminals for each eBike client.

