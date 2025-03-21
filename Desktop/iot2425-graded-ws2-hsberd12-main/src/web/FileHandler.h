#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <Poco/Net/HTTPRequestHandler.h>
#include <string>

class FileHandler : public Poco::Net::HTTPRequestHandler {
public:
    // Constructor updated to match the arguments
    FileHandler(const std::string& filename, const std::string& contentType, bool isError = false);

    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response);

private:
    std::string _filename;
    std::string _contentType;
    bool _isError;
};

#endif
