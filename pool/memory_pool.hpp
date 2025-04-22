#include <cstddef>
#include <cstdint>
#include <mutex>
#include <map>
#include <memory>
#include <new>

// A fixed‑size block pool: allocates blocks of exactly BlockSize bytes
class FixedBlockPool {
public:
    FixedBlockPool(std::size_t blockSize, std::size_t blocksPerChunk = 1024)
        : blockSize_(blockSize), blocksPerChunk_(blocksPerChunk),
        chunks_(nullptr), freeList_(nullptr)
    {
    }

    ~FixedBlockPool() {
        // free all chunks
        Chunk* c = chunks_;
        while (c) {
            Chunk* next = c->next;
            ::operator delete(static_cast<void*>(c));
            c = next;
        }
    }

    void* allocate() {
        std::lock_guard<std::mutex> lk(mutex_);
        if (!freeList_) allocateChunk();
        // pop one block off the free list
        void* p = freeList_;
        freeList_ = *reinterpret_cast<void**>(p);
        return p;
    }

    void deallocate(void* p) {
        std::lock_guard<std::mutex> lk(mutex_);
        // push back onto free list
        *reinterpret_cast<void**>(p) = freeList_;
        freeList_ = p;
    }

private:
    struct Chunk {
        Chunk* next;
        // immediately followed by blocksPerChunk_*blockSize_ bytes of data
    };

    void allocateChunk() {
        // allocate one big slab: Chunk header + N blocks
        std::size_t chunkBytes = sizeof(Chunk) + blockSize_ * blocksPerChunk_;
        Chunk* c = static_cast<Chunk*>(::operator new(chunkBytes));
        c->next = chunks_;
        chunks_ = c;

        // carve it into blocks, push onto free list
        std::uint8_t* block = reinterpret_cast<std::uint8_t*>(c + 1);
        for (std::size_t i = 0; i < blocksPerChunk_; ++i) {
            void* p = block + i * blockSize_;
            *reinterpret_cast<void**>(p) = freeList_;
            freeList_ = p;
        }
    }

    const std::size_t blockSize_;
    const std::size_t blocksPerChunk_;

    Chunk* chunks_;
    void* freeList_;
    std::mutex mutex_;
};


// Singleton manager: maps requested sizes → their FixedBlockPool
class MemoryPoolManager {
public:
    static MemoryPoolManager& instance() {
        static MemoryPoolManager mgr;
        return mgr;
    }

    // allocate a block of at least 'n' bytes
    void* allocate(std::size_t n) {
        auto& pool = getPool(roundUp(n));
        return pool.allocate();
    }

    // deallocate a block previously allocated with size 'n'
    void deallocate(void* p, std::size_t n) {
        auto it = pools_.find(roundUp(n));
        if (it != pools_.end())
            it->second->deallocate(p);
        // else: error or ignore
    }

private:
    MemoryPoolManager() = default;
    ~MemoryPoolManager() {
        for (auto& kv : pools_)
            delete kv.second;
    }

    // round up to nearest power-of-two class (or other granularity)
    static std::size_t roundUp(std::size_t n) {
        // here we round up to next multiple of 8 bytes
        constexpr std::size_t align = 8;
        return ((n + align - 1) / align) * align;
    }

    FixedBlockPool& getPool(std::size_t blockSize) {
        std::lock_guard<std::mutex> lk(managerMutex_);
        auto it = pools_.find(blockSize);
        if (it == pools_.end()) {
            // create a new sub-pool for this blockSize
            pools_[blockSize] = new FixedBlockPool(blockSize);
            it = pools_.find(blockSize);
        }
        return *it->second;
    }

    std::map<std::size_t, FixedBlockPool*> pools_;
    std::mutex managerMutex_;
};


// Convenience wrappers
inline void* pool_alloc(std::size_t n) {
    return MemoryPoolManager::instance().allocate(n);
}

inline void pool_free(void* p, std::size_t n) {
    MemoryPoolManager::instance().deallocate(p, n);
}