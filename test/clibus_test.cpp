#include <gtest/gtest.h>

extern void print_help();

TEST(PrintHelpTest, PrintsClibus) {
    testing::internal::CaptureStdout();
    print_help();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "clibus\n");
}
