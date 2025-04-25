#include <gtest/gtest.h>
#include <vector>
#include "sorting/heap_sort.hpp"

// Test sorting an empty vector
TEST(HeapSortTest, EmptyVector) {
    std::vector<int> vec;
    heapSort(vec.begin(), vec.end());
    EXPECT_TRUE(vec.empty());
}

// Test sorting a vector with one element
TEST(HeapSortTest, SingleElement) {
    std::vector<int> vec = {42};
    heapSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, std::vector<int>({42}));
}

// Test sorting a vector with multiple elements in ascending order
TEST(HeapSortTest, AscendingOrder) {
    std::vector<int> vec = {5, 3, 8, 6, 2, 7, 4, 1};
    heapSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8}));
}

// Test sorting a vector with multiple elements in descending order
TEST(HeapSortTest, DescendingOrder) {
    std::vector<int> vec = {5, 3, 8, 6, 2, 7, 4, 1};
    heapSort(vec.begin(), vec.end(), std::greater<int>());
    EXPECT_EQ(vec, std::vector<int>({8, 7, 6, 5, 4, 3, 2, 1}));
}

// Test sorting a vector with duplicate elements
TEST(HeapSortTest, Duplicates) {
    std::vector<int> vec = {4, 2, 4, 3, 1, 2, 5};
    heapSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, std::vector<int>({1, 2, 2, 3, 4, 4, 5}));
}

// Test sorting a vector that is already sorted
TEST(HeapSortTest, AlreadySorted) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    heapSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, std::vector<int>({1, 2, 3, 4, 5}));
}

// Test sorting a vector that is sorted in reverse order
TEST(HeapSortTest, ReverseSorted) {
    std::vector<int> vec = {5, 4, 3, 2, 1};
    heapSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, std::vector<int>({1, 2, 3, 4, 5}));
}

// Test sorting a vector with negative numbers
TEST(HeapSortTest, NegativeNumbers) {
    std::vector<int> vec = {-3, -1, -4, -2, 0};
    heapSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, std::vector<int>({-4, -3, -2, -1, 0}));
}

// Test sorting a vector with mixed positive and negative numbers
TEST(HeapSortTest, MixedNumbers) {
    std::vector<int> vec = {3, -1, 4, -2, 0};
    heapSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, std::vector<int>({-2, -1, 0, 3, 4}));
}
