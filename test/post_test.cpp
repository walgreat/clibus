#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "clibus/clibus.h"

class MockHttpClientWithPost : public HttpClientInterface {
public:
    MOCK_METHOD(std::string, get, (const std::string& path), (override));
    MOCK_METHOD(std::string, post, (const std::string& path), (override));
};

extern int fetch_url_with_client(const std::string& url, const std::string& method, std::unique_ptr<HttpClientInterface> client);

TEST(PostMethodTest, PostSuccess) {
    auto mock = std::unique_ptr<MockHttpClientWithPost>(new MockHttpClientWithPost());
    EXPECT_CALL(*mock, post("/")).WillOnce(testing::Return("post response"));

    testing::internal::CaptureStdout();
    int result = fetch_url_with_client("http://example.com", "POST", std::move(mock));
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(result, 0);
    EXPECT_EQ(output, "post response");
}

TEST(PostMethodTest, PostNetworkError) {
    auto mock = std::unique_ptr<MockHttpClientWithPost>(new MockHttpClientWithPost());
    EXPECT_CALL(*mock, post("/")).WillOnce(testing::Throw(std::runtime_error("connection failed")));

    testing::internal::CaptureStderr();
    int result = fetch_url_with_client("http://example.com", "POST", std::move(mock));
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(result, 1);
    EXPECT_EQ(output, "connection failed\n");
}

TEST(PostMethodTest, UnsupportedMethod) {
    auto mock = std::unique_ptr<MockHttpClientWithPost>(new MockHttpClientWithPost());

    testing::internal::CaptureStderr();
    int result = fetch_url_with_client("http://example.com", "PUT", std::move(mock));
    std::string output = testing::internal::GetCapturedStderr();

    EXPECT_EQ(result, 1);
    EXPECT_TRUE(output.find("Unsupported method") != std::string::npos);
}
