#ifndef CLIBUS_HTTP_CLIENT_H
#define CLIBUS_HTTP_CLIENT_H

#include "clibus/i_http_client.h"

namespace clibus {

class HttpClient : public IHttpClient {
public:
    HttpClient(const std::string& host, int port);
    ~HttpClient() override;

    HttpResponse get(const std::string& path) override;
    HttpResponse post(const std::string& path, const std::string& body) override;

private:
    std::string host_;
    int port_;
};

HttpClientPtr create_http_client(const std::string& host, int port);

}
#endif
