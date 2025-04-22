#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cstddef>
#include <string>

template <typename T>
class Array
{
private:
	T *data;
	size_t size;
	size_t capacity;

	void resize(size_t newCapacity)
	{
		// std::cout << "Resizing from " << capacity << " to " << newCapacity << std::endl;
		T *newData = new T[newCapacity];
		std::copy(data, data + size, newData);
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

public:
	explicit Array(size_t initialSize = 16) : size(0), capacity(initialSize)
	{
		data = new T[capacity];
	}
	Array(const Array<T> &other) : size(other.size), capacity(other.capacity)
	{
		data = new T[capacity];
		std::copy(other.data, other.data + size, data);
	}
	Array(Array<T> &&other) noexcept
	{
		data = other.data;
		size = other.size;
		capacity = other.capacity;
		other.data = nullptr;
		other.size = 0;
		other.capacity = 0;
	}
	~Array()
	{
		delete[] data;
	}
	Array<T> &operator=(const Array<T> &other)
	{
		if (this != &other)
		{
			delete[] data;
			size = other.size;
			capacity = other.capacity;
			data = new T[capacity];
			std::copy(other.data, other.data + size, data);
		}
		return *this;
	}
	void operator=(Array<T> &&other) noexcept
	{
		if (this != &other)
		{
			data = other.data;
			size = other.size;
			capacity = other.capacity;
			other.data = nullptr;
			other.size = 0;
			other.capacity = 0;
		}
		return *this;
	}
	void push_back(const T &value)
	{
		if (size == capacity)
			resize(capacity * 2);
		data[size++] = value;
	}
	void pop_back()
	{
		if (size == 0)
			throw std::runtime_error("Cannot pop from an empty array");
		size--;
	}
	T &at(size_t index) const
	{
		if (index >= size)
			throw std::out_of_range("Index out of range");
		return data[index];
	}
	T &front() const
	{
		if (size == 0)
			throw std::runtime_error("Cannot access front of an empty array");
		return data[0];
	}
	T &back() const
	{
		if (size == 0)
			throw std::runtime_error("Cannot access back of an empty array");
		return data[size - 1];
	}
	T &operator[](size_t index)
	{
		if (index >= size)
		{
			throw std::out_of_range("Index out of range");
		}
		return data[index];
	}
	size_t getSize() const
	{
		return size;
	}
	size_t getCapacity() const
	{
		return capacity;
	}
};