#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "clibus/clibus.h"

TEST(PrintHelpTest, PrintsClibus) {
    testing::internal::CaptureStdout();
    print_help();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "clibus\n");
}
