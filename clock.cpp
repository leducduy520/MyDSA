#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>
#include <memory>
#include <cassert>
#include <type_traits>
#include "sorting/merge_sort.hpp"
using namespace std::chrono;


int main()
{
    // Generate a large random array
    const size_t arraySize = 1'000'000; // 1 million elements
    std::vector<int> arr(arraySize);

    // Fill the array with random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1'000'000);
    std::generate(arr.begin(), arr.end(), [&]()
                  { return dis(gen); });

    auto start = high_resolution_clock::now();
    mergeSort(arr.begin(), arr.end(), std::less<int>{});
    auto end = high_resolution_clock::now();

    // Calculate and display the elapsed time
    auto duration = duration_cast<milliseconds>(end - start);
    std::cout << "Heap sort completed in " << duration.count() << " milliseconds." << std::endl;

    // Verify the array is sorted
    if (std::is_sorted(arr.begin(), arr.end()))
    {
        std::cout << "Array is sorted correctly." << std::endl;
    }
    else
    {
        std::cout << "Array is not sorted correctly." << std::endl;
    }
    return 0;
}