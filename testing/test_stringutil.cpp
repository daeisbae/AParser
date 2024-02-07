#include <gtest/gtest.h>

#include <queue>
#include <string>

#include "stringutil.hpp"

TEST(StringUtilTest, ConvertCharToString) {
  char input = 'a';
  std::string expected = "a";
  std::string result = ConvertCharToString(input);
  EXPECT_EQ(result, expected);
}

TEST(StringUtilTest, ConvertStringToQueue) {
  std::string input = "hello";
  std::queue<char> expected;
  std::array<char, 6> expected_arr{'h', 'e', 'l', 'l', 'o', '\0'};

  for (char ch : expected_arr) {
    expected.push(ch);
  }

  std::queue<char> result = ConvertStringToQueue(input);

  while (!expected.empty() && !result.empty()) {
    EXPECT_EQ(expected.front(), result.front());
    expected.pop();
    result.pop();
  }

  // Check that both queues are empty after popping all elements
  EXPECT_TRUE(expected.empty());
  EXPECT_TRUE(result.empty());
}