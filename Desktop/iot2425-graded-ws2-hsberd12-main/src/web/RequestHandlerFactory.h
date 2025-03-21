#ifndef RequestHandlerFactory_INCLUDED
#define RequestHandlerFactory_INCLUDED

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/JSON/Array.h>

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    RequestHandlerFactory(Poco::JSON::Array::Ptr ebikesData) : _ebikes(ebikesData) {}

    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;

private:
    Poco::JSON::Array::Ptr _ebikes;
};

#endif
