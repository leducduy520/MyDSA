#include <iostream>
#include <vector>
#include <functional>

// Helper function to "sift down" an element at index `i` in the heap
template<typename RandomIt, typename Compare>
void heapify(RandomIt first, RandomIt last, std::size_t i, Compare comp) {
    auto n = std::distance(first, last);
    std::size_t largest = i;
    std::size_t left = 2 * i + 1;
    std::size_t right = 2 * i + 2;

    // Check if left child exists and is greater than the current largest
    if (left < n && comp(*(first + largest), *(first + left))) {
        largest = left;
    }

    // Check if right child exists and is greater than the current largest
    if (right < n && comp(*(first + largest), *(first + right))) {
        largest = right;
    }

    // If the largest is not the current index, swap and heapify the affected subtree
    if (largest != i) {
        std::swap(*(first + i), *(first + largest));
        heapify(first, last, largest, comp); // Recursively heapify the affected subtree
    }
}

// Main function to perform heap sort
template<typename RandomIt, typename Compare>
void heapSort(RandomIt first, RandomIt last, Compare comp) {
    auto n = std::distance(first, last);
    if (n < 2)
        return;

    // Build the heap (rearrange the array)
    for (int i = n / 2 - 1; i != -1; --i) {
        heapify(first, last, static_cast<std::size_t>(i), comp);
    }

    // One by one, extract elements from the heap
    for (std::size_t i = n - 1; i > 0; --i) {
        // Move the current root to the end
        std::swap(*first, *(first + i));

        // Call heapify on the reduced heap
        heapify(first, first + i, 0, comp);
    }
}

// Convenience overload: defaults to ascending order using std::less<>
template<typename RandomIt>
void heapSort(RandomIt first, RandomIt last) {
    using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    heapSort(first, last, std::less<ValueType>());
}
