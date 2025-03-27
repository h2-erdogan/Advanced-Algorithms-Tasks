#ifndef EbikeHandler_INCLUDED
#define EbikeHandler_INCLUDED

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Object.h>   // BU VAR
#include <Poco/JSON/Array.h>    // BU YOKSA EKLE 🔥

class EbikeHandler : public Poco::Net::HTTPRequestHandler {
public:
    EbikeHandler(Poco::JSON::Array::Ptr ebikes);
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
    Poco::JSON::Array::Ptr _ebikes;
};

#endif
