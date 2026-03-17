#ifndef CLIBUS_MOCK_HTTP_CLIENT_H
#define CLIBUS_MOCK_HTTP_CLIENT_H

#include "clibus/i_http_client.h"

namespace clibus {

class MockHttpClient : public IHttpClient {
public:
    HttpResponse get(const std::string& path) override {
        return next_response_;
    }

    HttpResponse post(const std::string& path, const std::string& body) override {
        last_post_body_ = body;
        return next_response_;
    }

    void set_next_response(const HttpResponse& response) {
        next_response_ = response;
    }

    std::string get_last_post_body() const {
        return last_post_body_;
    }

private:
    HttpResponse next_response_;
    std::string last_post_body_;
};

inline HttpClientPtr create_mock_http_client() {
    return HttpClientPtr(new MockHttpClient());
}

}

#endif
