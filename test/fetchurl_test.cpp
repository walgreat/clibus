#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "clibus/clibus.h"

class MockHttpClient : public HttpClientInterface {
public:
    MOCK_METHOD(std::string, get, (const std::string& path), (override));
};

extern int fetch_url_with_client(const std::string& url, std::unique_ptr<HttpClientInterface> client);

TEST(FetchUrlTest, Success) {
    auto mock = std::unique_ptr<MockHttpClient>(new MockHttpClient());
    EXPECT_CALL(*mock, get("/")).WillOnce(testing::Return("mock response"));

    testing::internal::CaptureStdout();
    int result = fetch_url_with_client("http://example.com", std::move(mock));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, 0);
    EXPECT_EQ(output, "mock response");
}

TEST(FetchUrlTest, NetworkError) {
    auto mock = std::unique_ptr<MockHttpClient>(new MockHttpClient());
    EXPECT_CALL(*mock, get("/")).WillOnce(testing::Throw(std::runtime_error("connection failed")));

    testing::internal::CaptureStderr();
    int result = fetch_url_with_client("http://example.com", std::move(mock));
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(result, 1);
    EXPECT_EQ(output, "connection failed\n");
}

TEST(FetchUrlTest, HttpError) {
    auto mock = std::unique_ptr<MockHttpClient>(new MockHttpClient());
    EXPECT_CALL(*mock, get("/")).WillOnce(testing::Throw(std::runtime_error("HTTP error: 404")));

    testing::internal::CaptureStderr();
    int result = fetch_url_with_client("http://example.com/notfound", std::move(mock));
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(result, 1);
    EXPECT_EQ(output, "HTTP error: 404\n");
}