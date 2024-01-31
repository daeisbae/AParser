#include <string>

#include <gtest/gtest.h>
#include "stringutil.hpp"


TEST(ExtractTextOfLine, SplitingLineProperlyTesting) {
    EXPECT_EQ(ExtractTextOfLine("Good\tDay\n2You", 1), "Good\tDay");  
    EXPECT_EQ(ExtractTextOfLine("Hello\nWorld\nMyself", 3), "Myself");
}

TEST(ExtractTextOfLine, InvalidLineNumberTesting) {
    EXPECT_THROW(ExtractTextOfLine("Hello", 2), LineOutOfBoundException);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}