#include <iterator>   // for std::iterator_traits
#include <functional> // for std::less
#include <algorithm>  // for std::iter_swap
#include <utility>    // for std::swap

// Partition using Hoare’s scheme, returns the split point
template <typename RandomIt, typename Compare>
RandomIt xpartition(RandomIt first, RandomIt last, Compare comp)
{
    // pivot = middle element
    auto pivot = *(first + (std::distance(first, last) / 2));
    RandomIt left = first;
    RandomIt right = last;
    do
    {
        while (comp(*left, pivot))
            ++left;
        while (comp(pivot, *--right))
        { /* decrement in-place */
        }
        if (left < right)
        {
            std::iter_swap(left, right);
            ++left;
        }
    } while (left < right);
    return left;
}

template <typename RandomIt, typename Compare>
void quickSort(RandomIt first, RandomIt last, Compare comp)
{
    // only proceed if at least two elements
    if (std::distance(first, last) > 1)
    {
        RandomIt pivotPos = xpartition(first, last, comp);
        quickSort(first, pivotPos, comp);
        quickSort(pivotPos, last, comp);
    }
}

// Convenience overload: defaults to ascending order via std::less<>
template <typename RandomIt>
void quickSort(RandomIt first, RandomIt last)
{
    using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    quickSort(first, last, std::less<ValueType>{});
}
