#include "EbikeHandler.h"
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Array.h>  
#include <iostream>

EbikeHandler::EbikeHandler(Poco::JSON::Array::Ptr ebikes) : _ebikes(ebikes) {}

void EbikeHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    Poco::JSON::Object::Ptr responseObject = new Poco::JSON::Object;
    responseObject->set("ebikes", _ebikes);

    std::ostream& responseStream = response.send();
    responseObject->stringify(responseStream, 4);
    responseStream.flush();

    std::cout << "✅ Sent eBike JSON data to client!" << std::endl;
}
