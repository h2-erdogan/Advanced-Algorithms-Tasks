#ifndef WebServer_INCLUDED
#define WebServer_INCLUDED

#include <Poco/JSON/Array.h>

class WebServer {
public:
    WebServer(Poco::JSON::Array::Ptr ebikes);
    void start(int port);

private:
    Poco::JSON::Array::Ptr _ebikes;
};

#endif
