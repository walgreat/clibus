#include "clibus/http_client.h"

#include "httplib.h"

namespace clibus {

HttpClient::HttpClient(const std::string& host, int port)
    : host_(host), port_(port) {
}

HttpClient::~HttpClient() {
}

HttpResponse HttpClient::get(const std::string& path) {
    HttpResponse response;
    httplib::Client cli(host_, port_);

    auto result = cli.Get(path);

    if (result) {
        response.status = result->status;
        response.body = result->body;
    } else {
        response.status = 0;
        response.error = to_string(result.error());
    }

    return response;
}

HttpResponse HttpClient::post(const std::string& path, const std::string& body) {
    HttpResponse response;
    httplib::Client cli(host_, port_);

    auto result = cli.Post(path, body, "application/json");

    if (result) {
        response.status = result->status;
        response.body = result->body;
    } else {
        response.status = 0;
        response.error = to_string(result.error());
    }

    return response;
}

HttpClientPtr create_http_client(const std::string& host, int port) {
    return HttpClientPtr(new HttpClient(host, port));
}

}
