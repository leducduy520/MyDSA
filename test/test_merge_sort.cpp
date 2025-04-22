#include <gtest/gtest.h>
#include <numeric>
#include "sorting/merge_sort.hpp"

// Test merge_sort with an empty array
TEST(MergeSortTest, EmptyArray) {
    std::vector<int> arr;
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_TRUE(arr.empty());
}

// Test merge_sort with a single element
TEST(MergeSortTest, SingleElement) {
    std::vector<int> arr = {42};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

// Test merge_sort with already sorted array
TEST(MergeSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

// Test merge_sort with reverse sorted array
TEST(MergeSortTest, ReverseSorted) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

// Test merge_sort with duplicate elements
TEST(MergeSortTest, Duplicates) {
    std::vector<int> arr = {4, 2, 4, 3, 2, 1};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr, (std::vector<int>{1, 2, 2, 3, 4, 4}));
}

// Test merge_sort with negative numbers
TEST(MergeSortTest, NegativeNumbers) {
    std::vector<int> arr = {-3, -1, -4, -2, 0};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr, (std::vector<int>{-4, -3, -2, -1, 0}));
}

// Test merge_sort with mixed positive and negative numbers
TEST(MergeSortTest, MixedNumbers) {
    std::vector<int> arr = {3, -1, 4, -2, 0};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr, (std::vector<int>{-2, -1, 0, 3, 4}));
}

// Test merge_sort with large array
TEST(MergeSortTest, LargeArray) {
    std::vector<int> arr(1000);
    std::iota(arr.rbegin(), arr.rend(), 1); // Fill with 1000 to 1
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(arr[i], i + 1);
    }
}

// Test merge_sort with custom comparator
TEST(MergeSortTest, CustomComparator) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9};
    mergeSort(arr.begin(), arr.end(), std::greater<int>());
    EXPECT_EQ(arr, (std::vector<int>{9, 5, 4, 3, 1, 1}));
}

// Test merge_sort with floating-point numbers
TEST(MergeSortTest, FloatingPointNumbers) {
    std::vector<double> arr = {3.1, 2.2, 5.5, 4.4, 1.1};
    mergeSort(arr.begin(), arr.end(), std::less<double>());
    EXPECT_EQ(arr, (std::vector<double>{1.1, 2.2, 3.1, 4.4, 5.5}));
}

// Test merge_sort with strings
TEST(MergeSortTest, Strings) {
    std::vector<std::string> arr = {"banana", "apple", "cherry", "date"};
    mergeSort(arr.begin(), arr.end(), std::less<std::string>());
    EXPECT_EQ(arr, (std::vector<std::string>{"apple", "banana", "cherry", "date"}));
}

// Test merge_sort with all identical elements
TEST(MergeSortTest, IdenticalElements) {
    std::vector<int> arr = {7, 7, 7, 7, 7};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr, (std::vector<int>{7, 7, 7, 7, 7}));
}

// Test merge_sort with very small array
TEST(MergeSortTest, SmallArray) {
    std::vector<int> arr = {2, 1};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr, (std::vector<int>{1, 2}));
}

// Test merge_sort with large range of numbers
TEST(MergeSortTest, LargeRange) {
    std::vector<int> arr = {-1000, 500, 0, 1000, -500};
    mergeSort(arr.begin(), arr.end(), std::less<int>());
    EXPECT_EQ(arr, (std::vector<int>{-1000, -500, 0, 500, 1000}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}