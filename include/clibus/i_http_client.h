#ifndef CLIBUS_I_HTTP_CLIENT_H
#define CLIBUS_I_HTTP_CLIENT_H

#include <string>
#include <memory>

namespace clibus {

struct HttpResponse {
    int status = 0;
    std::string body;
    std::string error;

    bool ok() const { return status >= 200 && status < 300; }
};

class IHttpClient {
public:
    virtual ~IHttpClient() = default;

    virtual HttpResponse get(const std::string& path) = 0;
    virtual HttpResponse post(const std::string& path, const std::string& body) = 0;
};

using HttpClientPtr = std::unique_ptr<IHttpClient>;

}

#endif
