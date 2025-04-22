// File: test_linked_list.cpp
#include "data_structure/linked_list.hpp"
#include <gtest/gtest.h>
#include <string>

// Test List initialization
TEST(ListTest, ConstructorAndDestructor) {
    List<int> list;
    EXPECT_NO_THROW(list.clear());
}

// Test push_back
TEST(ListTest, PushBack) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 30 \n");
}

// Test push_front
TEST(ListTest, PushFront) {
    List<int> list;
    list.push_front(10);
    list.push_front(20);
    list.push_front(30);
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "30 20 10 \n");
}

// Test pop_back
TEST(ListTest, PopBack) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_back();
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 \n");
}

// Test pop_front
TEST(ListTest, PopFront) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.pop_front();
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "20 \n");
}

// Test insert
TEST(ListTest, Insert) {
    List<int> list;
    list.push_back(10);
    list.push_back(30);
    list.insert(1, 20);
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 30 \n");
}

// Test erase
TEST(ListTest, Erase) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.erase(1);
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 30 \n");
}

// Test clear
TEST(ListTest, Clear) {
    List<int> list;
    list.push_back(10);
    list.push_back(20);
    list.clear();
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "\n");
}

// Test edge cases
TEST(ListTest, EdgeCases) {
    List<int> list;

    // Pop from empty list
    EXPECT_THROW(list.pop_back(), std::out_of_range);
    EXPECT_THROW(list.pop_front(), std::out_of_range);

    // Insert at invalid index
    EXPECT_THROW(list.insert(1, 10), std::out_of_range);

    // Erase at invalid index
    EXPECT_THROW(list.erase(0), std::out_of_range);
}

// Test with different data types
TEST(ListTest, DifferentDataTypes) {
    List<std::string> list;
    list.push_back("Hello");
    list.push_back("World");
    testing::internal::CaptureStdout();
    list.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "Hello World \n");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}// File: test_linked_list.cpp
