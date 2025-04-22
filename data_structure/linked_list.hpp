#include <stdexcept>

template <typename T>
class List
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node *prev;
        Node(const T &data) : data(data), next(nullptr) {}
        Node(const Node &other) : data(other.data), next(other.next), prev(other.prev) {}
        Node &operator=(const Node &other)
        {
            if (this != &other)
            {
                data = other.data;
                next = other.next;
                prev = other.prev;
            }
            return *this;
        }
        ~Node() {}
    };
    Node *head;
    Node *tail;
    size_t size;

public:
    void clear()
    {
        while (head)
        {
            Node *tmp = head;
            head = head->next;
            delete tmp;
        }
    }
    List() : head(nullptr), tail(nullptr), size(0) {}
    ~List()
    {
        clear();
    }
    void push_back(const T &value)
    {
        Node *newNode = new Node(value);
        if (tail)
        {
            tail->next = newNode;
            newNode->prev = tail;
        }
        else
        {
            head = newNode;
        }
        tail = newNode;
        ++size;
    }
    void push_front(const T &value)
    {
        Node *newNode = new Node(value);
        if (head)
        {
            head->prev = newNode;
            newNode->next = head;
        }
        else
        {
            tail = newNode;
        }
        head = newNode;
        ++size;
    }
    void pop_back()
    {
        if (size == 0)
        {
            throw std::out_of_range("List is empty");
        }
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node *temp = tail;
            tail = tail->prev;
            tail->next = nullptr;
            delete temp;
        }
        --size;
    }
    void pop_front()
    {
        if (size == 0)
        {
            throw std::out_of_range("List is empty");
        }
        if (head == tail)
        {
            delete head;
            head = tail = nullptr;
        }
        else
        {
            Node *temp = head;
            head = head->next;
            head->prev = nullptr;
            delete temp;
        }
    }
    void insert(size_t index, const T &value)
    {
        if (index > size)
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            push_front(value);
            return;
        }
        if (index == size)
        {
            push_back(value);
            return;
        }
        Node *newNode = new Node(value);
        Node *current = nullptr;
        if (index < size / 2)
        {
            current = head;
            for (size_t i = 0; i < index; ++i)
            {
                current = current->next;
            }
        }
        else
        {
            current = tail;
            for (size_t i = size - 1; i > index; --i)
            {
                current = current->prev;
            }
        }
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
        ++size;
    }
    void erase(size_t index)
    {
        if (index >= size)
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            pop_front();
            return;
        }
        if (index == size - 1)
        {
            pop_back();
            return;
        }
        Node *current = nullptr;
        if (index < size / 2)
        {
            current = head;
            for (size_t i = 0; i < index; ++i)
            {
                current = current->next;
            }
        }
        else
        {
            current = tail;
            for (size_t i = size - 1; i > index; --i)
            {
                current = current->prev;
            }
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        --size;
    }
    void print() const
    {
        Node *current = head;
        while (current)
        {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }
};