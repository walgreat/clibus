#include <iostream>
#include "httplib.h"
#include "clibus/clibus.h"

class HttplibClient : public HttpClientInterface {
public:
    explicit HttplibClient(const std::string& base_url)
        : cli_(base_url) {
        cli_.set_connection_timeout(30);
    }

    std::string get(const std::string& path) override {
        auto res = cli_.Get(path);
        if (!res) {
            throw std::runtime_error("Request failed: " + httplib::to_string(res.error()));
        }
        if (res->status >= 400) {
            throw std::runtime_error("HTTP error: " + std::to_string(res->status));
        }
        return res->body;
    }

private:
    httplib::Client cli_;
};

void print_help() {
    std::cout << "clibus" << std::endl;
}

int fetch_url(const std::string& url) {
    return fetch_url_with_client(url, std::unique_ptr<HttpClientInterface>(new HttplibClient(url)));
}

int fetch_url_with_client(const std::string& url, std::unique_ptr<HttpClientInterface> client) {
    try {
        std::cout << client->get("/");
        return 0;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
