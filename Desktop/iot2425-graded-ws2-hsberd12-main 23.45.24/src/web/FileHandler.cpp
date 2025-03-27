#include "FileHandler.h"
#include <Poco/Net/HTTPServerResponse.h>
#include <fstream>
#include <streambuf>

FileHandler::FileHandler(const std::string& filename, const std::string& contentType, bool isError)
    : _filename(filename), _contentType(contentType), _isError(isError) {}

void FileHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.setChunkedTransferEncoding(true);
    response.setContentType(_contentType);

    std::ostream& responseStream = response.send();

    if (_isError) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        responseStream << "404 Not Found";
    } else {
        std::ifstream file(_filename);
        if (file.is_open()) {
            responseStream << file.rdbuf();
            file.close();
        } else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            responseStream << "404 Not Found - File Missing";
        }
    }

    responseStream.flush();
}
