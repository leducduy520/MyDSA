#include "pool/memory_pool.hpp"
#include <gtest/gtest.h>

// Test FixedBlockPool initialization
TEST(FixedBlockPoolTest, ConstructorAndDestructor) {
    FixedBlockPool pool(32); // Block size of 32 bytes
    EXPECT_NO_THROW(pool.allocate());
}

// Test allocate and deallocate
TEST(FixedBlockPoolTest, AllocateAndDeallocate) {
    FixedBlockPool pool(32);
    void* block1 = pool.allocate();
    void* block2 = pool.allocate();
    EXPECT_NE(block1, nullptr);
    EXPECT_NE(block2, nullptr);
    EXPECT_NE(block1, block2);
    EXPECT_NO_THROW(pool.deallocate(block1));
    EXPECT_NO_THROW(pool.deallocate(block2));
}

// Test allocateChunk (indirectly through multiple allocations)
TEST(FixedBlockPoolTest, AllocateChunk) {
    FixedBlockPool pool(32, 2); // 2 blocks per chunk
    void* block1 = pool.allocate();
    void* block2 = pool.allocate();
    void* block3 = pool.allocate(); // Should trigger a new chunk allocation
    EXPECT_NE(block1, nullptr);
    EXPECT_NE(block2, nullptr);
    EXPECT_NE(block3, nullptr);
    EXPECT_NO_THROW(pool.deallocate(block1));
    EXPECT_NO_THROW(pool.deallocate(block2));
    EXPECT_NO_THROW(pool.deallocate(block3));
}

// Test deallocate invalid pointer
TEST(FixedBlockPoolTest, DeallocateInvalidPointer) {
    FixedBlockPool pool(32);
    int invalidValue = 42;
    void* invalidPtr = &invalidValue;
    EXPECT_NO_THROW(pool.deallocate(invalidPtr)); // Should handle gracefully
}

// Test MemoryPoolManager singleton instance
TEST(MemoryPoolManagerTest, SingletonInstance) {
    MemoryPoolManager& manager1 = MemoryPoolManager::instance();
    MemoryPoolManager& manager2 = MemoryPoolManager::instance();
    EXPECT_EQ(&manager1, &manager2); // Both should point to the same instance
}

// Test MemoryPoolManager allocate and deallocate
TEST(MemoryPoolManagerTest, AllocateAndDeallocate) {
    MemoryPoolManager& manager = MemoryPoolManager::instance();
    void* block = manager.allocate(64); // Request 64 bytes
    EXPECT_NE(block, nullptr);
    EXPECT_NO_THROW(manager.deallocate(block, 64));
}

// Test MemoryPoolManager allocate with varying sizes
TEST(MemoryPoolManagerTest, AllocateVaryingSizes) {
    MemoryPoolManager& manager = MemoryPoolManager::instance();
    void* block1 = manager.allocate(32);
    void* block2 = manager.allocate(64);
    EXPECT_NE(block1, nullptr);
    EXPECT_NE(block2, nullptr);
    EXPECT_NO_THROW(manager.deallocate(block1, 32));
    EXPECT_NO_THROW(manager.deallocate(block2, 64));
}

// Test MemoryPoolManager deallocate invalid pointer
TEST(MemoryPoolManagerTest, DeallocateInvalidPointer) {
    MemoryPoolManager& manager = MemoryPoolManager::instance();
    int invalidValue = 42;
    void* invalidPtr = &invalidValue;
    EXPECT_NO_THROW(manager.deallocate(invalidPtr, 32)); // Should handle gracefully
}

// Test convenience wrappers: pool_alloc and pool_free
TEST(MemoryPoolConvenienceWrappersTest, PoolAllocAndFree) {
    void* block = pool_alloc(128); // Allocate 128 bytes
    EXPECT_NE(block, nullptr);
    EXPECT_NO_THROW(pool_free(block, 128)); // Free the allocated block
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}