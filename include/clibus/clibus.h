#ifndef CLIBUS_H
#define CLIBUS_H

#include <string>
#include <memory>

class HttpClientInterface {
public:
    virtual ~HttpClientInterface() = default;
    virtual std::string get(const std::string& path) = 0;
    virtual std::string post(const std::string& path) {
        throw std::runtime_error("POST not implemented");
    }
};

void print_help();
int fetch_url(const std::string& url);
int fetch_url_with_client(const std::string& url, std::unique_ptr<HttpClientInterface> client);
int fetch_url(const std::string& url, const std::string& method);
int fetch_url_with_client(const std::string& url, const std::string& method, std::unique_ptr<HttpClientInterface> client);

#endif
