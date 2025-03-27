#include "RequestHandlerFactory.h"
#include "FileHandler.h"
#include "EbikeHandler.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/JSON/Object.h>

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {

    if (request.getURI() == "/" || request.getURI() == "/ebikes") {
        // Return EbikeHandler to serve JSON data
        return new EbikeHandler(_ebikes);
    } else if (request.getURI() == "/map.html") {
        // Return FileHandler to serve HTML file
        return new FileHandler("src/html/map.html", "text/html");
    } else {
        // Return a simple 404 response for other requests
        return new FileHandler("", "text/plain", true);
    }
}
