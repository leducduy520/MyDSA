#include <gtest/gtest.h>
#include <vector>
#include "sorting/insertion_sort.hpp"

// Test sorting an empty vector
TEST(InsertionSortTest, EmptyVector) {
    std::vector<int> vec;
    insertionSort(vec.begin(), vec.end());
    EXPECT_TRUE(vec.empty());
}

// Test sorting a vector with one element
TEST(InsertionSortTest, SingleElement) {
    std::vector<int> vec = {42};
    insertionSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, std::vector<int>({42}));
}

// Test sorting a vector with multiple elements in ascending order
TEST(InsertionSortTest, AscendingOrder) {
    std::vector<int> vec = {5, 3, 8, 6, 2, 7, 4, 1};
    insertionSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8}));
}

// Test sorting a vector with multiple elements in descending order
TEST(InsertionSortTest, DescendingOrder) {
    std::vector<int> vec = {8, 7, 6, 5, 4, 3, 2, 1};
    insertionSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8}));
}

// Test sorting a vector with duplicate elements
TEST(InsertionSortTest, Duplicates) {
    std::vector<int> vec = {4, 2, 4, 3, 1, 2, 3, 1};
    insertionSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, (std::vector<int>{1, 1, 2, 2, 3, 3, 4, 4}));
}

// Test sorting a vector that is already sorted
TEST(InsertionSortTest, AlreadySorted) {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    insertionSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8}));
}

// Test sorting a vector that is sorted in reverse order
TEST(InsertionSortTest, ReverseSorted) {
    std::vector<int> vec = {8, 7, 6, 5, 4, 3, 2, 1};
    insertionSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, (std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8}));
}

// Test sorting a vector with negative numbers
TEST(InsertionSortTest, NegativeNumbers) {
    std::vector<int> vec = {-3, -1, -4, -2, 0, 2, 1};
    insertionSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, (std::vector<int>{-4, -3, -2, -1, 0, 1, 2}));
}

// Test sorting a vector with mixed positive and negative numbers
TEST(InsertionSortTest, MixedNumbers) {
    std::vector<int> vec = {3, -1, 4, -2, 0, -5, 2, 1};
    insertionSort(vec.begin(), vec.end());
    EXPECT_EQ(vec, (std::vector<int>{-5, -2, -1, 0, 1, 2, 3, 4}));
}