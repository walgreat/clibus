#ifndef CLIBUS_H
#define CLIBUS_H

#include <string>
#include <memory>

class HttpClientInterface {
public:
    virtual ~HttpClientInterface() = default;
    virtual std::string get(const std::string& path) = 0;
};

void print_help();
int fetch_url(const std::string& url);
int fetch_url_with_client(const std::string& url, std::unique_ptr<HttpClientInterface> client);

#endif
