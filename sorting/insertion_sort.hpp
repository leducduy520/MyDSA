#include <vector>
#include <iterator>
#include <algorithm>

template <typename RandomIt, typename Compare>
void insertionSort(RandomIt begin, RandomIt end, Compare comp) {
    if (begin == end || std::next(begin) == end) {
        return;
    }

    for (RandomIt i = std::next(begin); i != end; ++i) {
        typename std::iterator_traits<RandomIt>::value_type key = *i;
        RandomIt j = i;
        
        while (j != begin && *(std::prev(j)) > key) {
            *j = *(std::prev(j));
            --j;
        }
        
        *j = key;
    }
}

template <typename RandomIt>
void insertionSort(RandomIt first, RandomIt last)
{
    using ValueType = std::iterator_traits<RandomIt>::value_type;
    insertionSort(first, last, std::less<ValueType>{});
}