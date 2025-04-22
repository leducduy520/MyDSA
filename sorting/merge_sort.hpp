#include <vector>
#include <iterator>
#include <functional>
#include <algorithm>

// Merge‑sort with custom comparator
template <typename RandomIt, typename Compare>
void mergeSort(RandomIt first, RandomIt last, Compare comp)
{
    auto n = std::distance(first, last);
    if (n < 2)
        return; // zero or one element is already sorted

    RandomIt mid = first + n / 2;
    // sort both halves
    mergeSort(first, mid, comp);
    mergeSort(mid, last, comp);

    using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    std::vector<ValueType> buffer;
    buffer.reserve(n);

    // merge from [first, mid) and [mid, last) into buffer
    RandomIt left = first, right = mid;
    while (left != mid && right != last)
    {
        if (comp(*right, *left))
        {
            buffer.push_back(*right++);
        }
        else
        {
            buffer.push_back(*left++);
        }
    }
    // append any leftovers
    buffer.insert(buffer.end(), left, mid);
    buffer.insert(buffer.end(), right, last);

    // copy back into original range
    std::move(buffer.begin(), buffer.end(), first);
}

// Convenience overload: ascending order via std::less<>
template <typename RandomIt>
void merge_sort(RandomIt first, RandomIt last)
{
    using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    merge_sort(first, last, std::less<ValueType>{});
}
