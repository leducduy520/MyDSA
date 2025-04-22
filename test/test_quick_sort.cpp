#include <gtest/gtest.h>
#include <numeric>
#include "sorting/quick_sort.hpp"

// Test quick_sort with an empty array
TEST(QuickSortTest, EmptyArray) {
    std::vector<int> arr;
    quickSort(arr.begin(), arr.end());
    EXPECT_TRUE(arr.empty());
}

// Test quick_sort with a single element
TEST(QuickSortTest, SingleElement) {
    std::vector<int> arr = {42};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

// Test quick_sort with already sorted array
TEST(QuickSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

// Test quick_sort with reverse sorted array
TEST(QuickSortTest, ReverseSorted) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<int>{1, 2, 3, 4, 5}));
}

// Test quick_sort with duplicate elements
TEST(QuickSortTest, Duplicates) {
    std::vector<int> arr = {4, 2, 4, 3, 2, 1};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<int>{1, 2, 2, 3, 4, 4}));
}

// Test quick_sort with negative numbers
TEST(QuickSortTest, NegativeNumbers) {
    std::vector<int> arr = {-3, -1, -4, -2, 0};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<int>{-4, -3, -2, -1, 0}));
}

// Test quick_sort with mixed positive and negative numbers
TEST(QuickSortTest, MixedNumbers) {
    std::vector<int> arr = {3, -1, 4, -2, 0};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<int>{-2, -1, 0, 3, 4}));
}

// Test quick_sort with large array
TEST(QuickSortTest, LargeArray) {
    std::vector<int> arr(1000);
    std::iota(arr.rbegin(), arr.rend(), 1); // Fill with 1000 to 1
    quickSort(arr.begin(), arr.end());
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(arr[i], i + 1);
    }
}

// Test quick_sort with custom comparator
TEST(QuickSortTest, CustomComparator) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9};
    quickSort(arr.begin(), arr.end(), std::greater<int>());
    EXPECT_EQ(arr, (std::vector<int>{9, 5, 4, 3, 1, 1}));
}

// Test quick_sort with floating-point numbers
TEST(QuickSortTest, FloatingPointNumbers) {
    std::vector<double> arr = {3.1, 2.2, 5.5, 4.4, 1.1};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<double>{1.1, 2.2, 3.1, 4.4, 5.5}));
}

// Test quick_sort with strings
TEST(QuickSortTest, Strings) {
    std::vector<std::string> arr = {"banana", "apple", "cherry", "date"};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<std::string>{"apple", "banana", "cherry", "date"}));
}

// Test quick_sort with all identical elements
TEST(QuickSortTest, IdenticalElements) {
    std::vector<int> arr = {7, 7, 7, 7, 7};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<int>{7, 7, 7, 7, 7}));
}

// Test quick_sort with very small array
TEST(QuickSortTest, SmallArray) {
    std::vector<int> arr = {2, 1};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<int>{1, 2}));
}

// Test quick_sort with large range of numbers
TEST(QuickSortTest, LargeRange) {
    std::vector<int> arr = {-1000, 500, 0, 1000, -500};
    quickSort(arr.begin(), arr.end());
    EXPECT_EQ(arr, (std::vector<int>{-1000, -500, 0, 500, 1000}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
