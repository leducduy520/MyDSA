#include <stdexcept>

template <typename T>
class Deque
{
    struct Chunk
    {
        T *data;
        size_t size;
        size_t capacity;
        Chunk *next;
        Chunk *prev;
        Chunk(size_t cap)
            : data(new T[cap]), size(0), capacity(cap),
              next(nullptr), prev(nullptr) {}
        Chunk(const Chunk &other)
            : size(other.size), capacity(other.capacity), next(other.next),
              prev(other.prev)
        {
            data = new T[capacity];
            std::copy(other.data, other.data + size, data);
        }
        Chunk &operator=(const Chunk &other)
        {
            if (this != &other)
            {
                delete[] data;
                size = other.size;
                capacity = other.capacity;
                next = other.next;
                prev = other.prev;
                data = new T[capacity];
                std::copy(other.data, other.data + size, data);
            }
            return *this;
        }
        ~Chunk() { delete[] data; }
    };
    Chunk *head;
    Chunk *tail;
    size_t chunk_size;
    size_t total_size;
    void push_back_chunk()
    {
        if (tail == nullptr || tail->size == chunk_size)
        {
            Chunk *new_chunk = new Chunk(chunk_size);
            if (tail)
            {
                new_chunk->prev = tail;
                tail->next = new_chunk;
            }
            else
            {
                head = new_chunk;
            }
            tail = new_chunk;
        }
    }
    void push_front_chunk()
    {
        if (head == nullptr || head->size == chunk_size)
        {
            Chunk *new_chunk = new Chunk(chunk_size);
            if (head)
            {
                new_chunk->next = head;
                head->prev = new_chunk;
            }
            else
            {
                tail = new_chunk;
            }
            head = new_chunk;
        }
    }
    void pop_back_chunk()
    {
        if (head == tail && tail->size == 0)
        {
            delete tail;
            head = tail = nullptr;
        }
        else if (tail->size == 0)
        {
            Chunk *temp = tail;
            tail = tail->prev;
            delete temp;
        }
    }
    void pop_front_chunk()
    {
        if (head == tail && head->size == 0)
        {
            delete head;
            head = tail = nullptr;
        }
        else if (head->size == 0)
        {
            Chunk *temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    
    void clear()
    {
        while (head)
        {
            Chunk *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        total_size = 0;
    }
    Deque(size_t chunk_size = 4) : head(nullptr), tail(nullptr), chunk_size(chunk_size), total_size(0) {}
    Deque(const Deque &other)
    {
        clear();
        chunk_size = other.chunk_size;
        total_size = other.total_size;
        Chunk *current = other.head;
        while (current)
        {
            Chunk *new_chunk = new Chunk(*current);
            if (tail)
            {
                tail->next = new_chunk;
                new_chunk->prev = tail;
            }
            else
            {
                head = new_chunk;
            }
            tail = new_chunk;
            current = current->next;
        }
    }
    Deque &operator=(const Deque &other)
    {
        if (this != &other)
        {
            clear();
            chunk_size = other.chunk_size;
            total_size = other.total_size;
            Chunk *current = other.head;
            while (current)
            {
                Chunk *new_chunk = new Chunk(*current);
                if (tail)
                {
                    tail->next = new_chunk;
                    new_chunk->prev = tail;
                }
                else
                {
                    head = new_chunk;
                }
                tail = new_chunk;
                current = current->next;
            }
        }
        return *this;
    }
    Deque(Deque &&other) noexcept
        : head(other.head), tail(other.tail), chunk_size(other.chunk_size), total_size(other.total_size)
    {
        other.head = nullptr;
        other.tail = nullptr;
        other.total_size = 0;
    }
    Deque &operator=(Deque &&other) noexcept
    {
        if (this != &other)
        {
            clear();
            head = other.head;
            tail = other.tail;
            chunk_size = other.chunk_size;
            total_size = other.total_size;
            other.head = nullptr;
            other.tail = nullptr;
            other.total_size = 0;
        }
        return *this;
    }
    ~Deque()
    {
        while (head)
        {
            Chunk *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void push_back(int value)
    {
        push_back_chunk();
        tail->data[tail->size++] = value;
        ++total_size;
    }
    void push_front(int value)
    {
        Chunk *old_head = head;
        push_front_chunk();
        if (old_head == head)
        {
            for (size_t i = head->size; i > 0; --i)
            {
                head->data[i] = head->data[i - 1];
            }
        }
        head->data[0] = value;
        head->size++;
        ++total_size;
    }
    void pop_back()
    {
        if (total_size == 0)
        {
            throw std::runtime_error("Deque is empty");
        }
        --tail->size;
        --total_size;
        pop_back_chunk();
    }
    void pop_front()
    {
        if (total_size == 0)
        {
            throw std::runtime_error("Deque is empty");
        }
        Chunk *old_head = head;
        --head->size;
        --total_size;
        pop_front_chunk();
        if (old_head == head)
        {
            for (size_t i = 0; i < head->size; ++i)
            {
                head->data[i] = head->data[i + 1];
            }
        }
    }
    T &front() const
    {
        if (total_size == 0)
        {
            throw std::runtime_error("Deque is empty");
        }
        return head->data[0];
    }
    T &back() const
    {
        if (total_size == 0)
        {
            throw std::runtime_error("Deque is empty");
        }
        return tail->data[tail->size - 1];
    }
    T &at(size_t index) const
    {
        if (index >= total_size)
        {
            throw std::out_of_range("Index out of range");
        }
        Chunk *current = head;
        while (index >= current->size)
        {
            index -= current->size;
            current = current->next;
        }
        return current->data[index];
    }
    size_t size() const { return total_size; }
    T &operator[](size_t index) { return at(index); }
    void print() const
    {
        Chunk *current = head;
        while (current)
        {
            for (size_t i = 0; i < current->size; ++i)
            {
                std::cout << current->data[i] << " ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};