#include <vector>
#include <stdexcept>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue
{
public:
    const T &front() const
    {
        if (_data.empty())
            throw std::out_of_range("Queue is empty!");
        return _data.front();
    }
    void push(const T &value)
    {
        _data.push_back(value);
        shiftUp(_data.size() - 1);
    }
    void pop()
    {
        if (_data.empty())
            throw std::out_of_range("Queue is empty!");
        std::swap(_data.front(), _data.back());
        _data.pop_back();
        if (!_data.empty())
            shiftDown(0);
    }

private:
    std::vector<T> _data;
    Compare _cmp;
    void shiftUp(size_t idx)
    {
        if (idx <= 0)
            return;
        size_t parent = (idx - 1) / 2;
        if (!_cmp(_data[parent], _data[idx]))
            return;
        std::swap(_data[parent], _data[idx]);
        idx = parent;
        shiftUp(idx);
    }
    void shiftDown(size_t idx)
    {
        size_t n = _data.size();
        size_t left = idx * 2 + 1;
        size_t right = idx * 2 + 2;
        size_t largest = idx;
        if (left < n && _cmp(_data[largest], _data[left]))
        {
            largest = left;
        }
        if (right < n && _cmp(_data[largest], _data[right]))
        {
            largest = right;
        }
        if (largest != idx)
        {
            std::swap(_data[largest], _data[idx]);
            shiftDown(largest);
        }
    }
};