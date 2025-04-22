#include "data_structure/deque.hpp"
#include <gtest/gtest.h>

// Test Deque initialization
TEST(DequeTest, ConstructorAndDestructor) {
    Deque<int> deque;
    EXPECT_NO_THROW(deque.push_back(1));
    EXPECT_NO_THROW(deque.pop_back());
}

// Test push_back
TEST(DequeTest, PushBack) {
    Deque<int> deque;
    for (int i = 0; i < 10; ++i) {
        deque.push_back(i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(deque.at(i), i);
    }
}

// Test push_front
TEST(DequeTest, PushFront) {
    Deque<int> deque;
    for (int i = 0; i < 10; ++i) {
        deque.push_front(i);
    }
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(deque.at(i), 9 - i);
    }
}

// Test pop_back
TEST(DequeTest, PopBack) {
    Deque<int> deque;
    deque.push_back(1);
    deque.push_back(2);
    deque.pop_back();
    EXPECT_EQ(deque.back(), 1);
    deque.pop_back();
    EXPECT_THROW(deque.pop_back(), std::runtime_error);
}

// Test pop_front
TEST(DequeTest, PopFront) {
    Deque<int> deque;
    deque.push_back(1);
    deque.push_back(2);
    deque.pop_front();
    EXPECT_EQ(deque.front(), 2);
    deque.pop_front();
    EXPECT_THROW(deque.pop_front(), std::runtime_error);
}

// Test at
TEST(DequeTest, At) {
    Deque<int> deque;
    deque.push_back(10);
    deque.push_back(20);
    EXPECT_EQ(deque.at(0), 10);
    EXPECT_EQ(deque.at(1), 20);
    EXPECT_THROW(deque.at(2), std::out_of_range);
}

// Test front and back
TEST(DequeTest, FrontAndBack) {
    Deque<int> deque;
    deque.push_back(5);
    deque.push_back(10);
    EXPECT_EQ(deque.front(), 5);
    EXPECT_EQ(deque.back(), 10);
    deque.pop_back();
    EXPECT_EQ(deque.back(), 5);
}

// Test operator[]
TEST(DequeTest, OperatorSquareBrackets) {
    Deque<int> deque;
    deque.push_back(100);
    deque.push_back(200);
    EXPECT_EQ(deque[0], 100);
    EXPECT_EQ(deque[1], 200);
    EXPECT_THROW(deque[2], std::out_of_range);
}

// Test assignment operator
TEST(DequeTest, AssignmentOperator) {
    Deque<int> deque1;
    for (int i = 0; i < 5; ++i) {
        deque1.push_back(i);
    }
    Deque<int> deque2;
    deque2 = deque1;
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(deque2[i], i);
    }
}

// Test move assignment operator
TEST(DequeTest, MoveAssignmentOperator) {
    Deque<int> deque1;
    for (int i = 0; i < 5; ++i) {
        deque1.push_back(i);
    }
    Deque<int> deque2 = std::move(deque1);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(deque2[i], i);
    }
    EXPECT_THROW(deque1.front(), std::runtime_error); // deque1 should be empty
}

// Test edge cases
TEST(DequeTest, EdgeCases) {
    Deque<int> deque;
    EXPECT_THROW(deque.front(), std::runtime_error);
    EXPECT_THROW(deque.back(), std::runtime_error);
    EXPECT_THROW(deque.pop_back(), std::runtime_error);
    EXPECT_THROW(deque.pop_front(), std::runtime_error);
    EXPECT_THROW(deque.at(0), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}