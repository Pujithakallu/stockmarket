// 4.) Write a custom memory allocator in C++ that: Allocates memory in chunks from a large pre-
// allocated pool.

// • Tracks allocated and freed memory to reuse blocks efficiently.
// • Supports allocating and freeing memory of various sizes.
// • Demonstrate its usage by creating and freeing several objects dynamically.

#include <iostream>
#include <vector>

class MemoryPool {
    std::vector<char> pool;
    size_t blockSize;
    size_t poolSize;
    std::vector<char*> freeList;

public:
    MemoryPool(size_t blockSize, size_t poolSize)
        : blockSize(blockSize), poolSize(poolSize) {
        pool.resize(poolSize * blockSize);
        for (size_t i = 0; i < poolSize; ++i) {
            freeList.push_back(&pool[i * blockSize]);
        }
    }

    void* allocate() {
        if (freeList.empty()) {
            throw std::bad_alloc();
        }
        void* block = freeList.back();
        freeList.pop_back();
        return block;
    }

    void deallocate(void* ptr) {
        freeList.push_back(static_cast<char*>(ptr));
    }
};

int main() {
    MemoryPool pool(256, 10);  // 256 bytes per block, 10 blocks
    
    void* obj1 = pool.allocate();
    void* obj2 = pool.allocate();

    pool.deallocate(obj1);
    pool.deallocate(obj2);

    std::cout << "Memory operations completed successfully." << std::endl;

    return 0;
}
