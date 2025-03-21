#include "WebServer.h"
#include "RequestHandlerFactory.h"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServer.h>
#include <iostream>
#include <thread>

WebServer::WebServer(Poco::JSON::Array::Ptr ebikes) : _ebikes(ebikes) {}

void WebServer::start(int port) {
    Poco::Net::ServerSocket socket(port);
    Poco::Net::HTTPServerParams* params = new Poco::Net::HTTPServerParams;
    Poco::Net::HTTPServer server(new RequestHandlerFactory(_ebikes), socket, params);

    server.start();

    std::cout << "Server started on http://localhost:" << port << std::endl;
    std::cout << "Press Ctrl+C to stop the server..." << std::endl;

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
