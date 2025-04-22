#include <gtest/gtest.h>
#include "data_structure/priority_queue.hpp"

// Test PriorityQueue initialization
TEST(PriorityQueueTest, Constructor) {
    PriorityQueue<int> pq;
    EXPECT_NO_THROW(pq.push(10));
    EXPECT_NO_THROW(pq.pop());
}

// Test push and front
TEST(PriorityQueueTest, PushAndFront) {
    PriorityQueue<int> pq;
    pq.push(10);
    EXPECT_EQ(pq.front(), 10);
    pq.push(20);
    EXPECT_EQ(pq.front(), 20); // Assuming max-heap behavior
    pq.push(5);
    EXPECT_EQ(pq.front(), 20);
}

// Test pop
TEST(PriorityQueueTest, Pop) {
    PriorityQueue<int> pq;
    pq.push(10);
    pq.push(20);
    pq.push(5);
    pq.pop();
    EXPECT_EQ(pq.front(), 10);
    pq.pop();
    EXPECT_EQ(pq.front(), 5);
    pq.pop();
    EXPECT_THROW(pq.pop(), std::out_of_range);
}

// Test front on an empty queue
TEST(PriorityQueueTest, FrontEmptyQueue) {
    PriorityQueue<int> pq;
    EXPECT_THROW(pq.front(), std::out_of_range);
}

// Test custom comparator (min-heap)
TEST(PriorityQueueTest, CustomComparator) {
    PriorityQueue<int, std::greater<int>> pq; // Min-heap
    pq.push(10);
    pq.push(20);
    pq.push(5);
    EXPECT_EQ(pq.front(), 5);
    pq.pop();
    EXPECT_EQ(pq.front(), 10);
    pq.pop();
    EXPECT_EQ(pq.front(), 20);
}

// Test large number of elements
TEST(PriorityQueueTest, LargeNumberOfElements) {
    PriorityQueue<int> pq;
    for (int i = 0; i < 1000; ++i) {
        pq.push(i);
    }
    EXPECT_EQ(pq.front(), 999);
    for (int i = 999; i >= 0; --i) {
        EXPECT_EQ(pq.front(), i);
        pq.pop();
    }
    EXPECT_THROW(pq.pop(), std::out_of_range);
}

// Test stability with duplicate elements
TEST(PriorityQueueTest, DuplicateElements) {
    PriorityQueue<int> pq;
    pq.push(10);
    pq.push(10);
    pq.push(20);
    EXPECT_EQ(pq.front(), 20);
    pq.pop();
    EXPECT_EQ(pq.front(), 10);
    pq.pop();
    EXPECT_EQ(pq.front(), 10);
    pq.pop();
    EXPECT_THROW(pq.pop(), std::out_of_range);
}

// Test edge cases
TEST(PriorityQueueTest, EdgeCases) {
    PriorityQueue<int> pq;
    EXPECT_THROW(pq.pop(), std::out_of_range); // Pop from empty queue
    EXPECT_THROW(pq.front(), std::out_of_range); // Front on empty queue
    pq.push(42);
    EXPECT_NO_THROW(pq.pop());
    EXPECT_THROW(pq.pop(), std::out_of_range);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
