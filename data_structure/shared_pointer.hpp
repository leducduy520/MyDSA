
template <typename T>
class SharedPointer
{
private:
    T *ptr;
    size_t *ref_count;
    void release()
    {
        if (ptr == nullptr && *ref_count == 0)
            return;
        if (--(*ref_count) == 0)
        {
            if (ptr)
            {
                delete ptr;
            }
            delete ref_count;
            ref_count = nullptr;
            ptr = nullptr;
        }
    }

public:
    SharedPointer() : ptr(nullptr), ref_count(new size_t(0)) {}
    SharedPointer(T *p) : ptr(p), ref_count(new size_t(1)) {}
    SharedPointer(const SharedPointer &other) : ptr(other.ptr), ref_count(other.ref_count)
    {
        ++(*ref_count);
    }
    SharedPointer(SharedPointer &&other) noexcept : ptr(other.ptr), ref_count(other.ref_count)
    {
        other.ptr = nullptr;
        other.ref_count = new size_t(0);
    }
    SharedPointer &operator=(const SharedPointer &other)
    {
        if (this != &other)
        {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            ++(*ref_count);
        }
        return *this;
    }
    SharedPointer &operator=(SharedPointer &&other) noexcept
    {
        if (this != &other)
        {
            release();
            ptr = other.ptr;
            ref_count = other.ref_count;
            other.ptr = nullptr;
            other.ref_count = new size_t(0);
        }
        return *this;
    }
    ~SharedPointer()
    {
        release();
    }
    size_t use_count() const
    {
        return *ref_count;
    }
    T &operator*() const
    {
        return *ptr;
    }
    T *operator->() const
    {
        return ptr;
    }
    T *get() const
    {
        return ptr;
    }
    void reset(T *p = nullptr)
    {
        release();
        ptr = p;
        ref_count = new size_t(1);
    }
    explicit operator bool() const
    {
        return ptr != nullptr;
    }
};