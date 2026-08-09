#include "./RFixedPool.hpp"

#define             TOTAL_CAPACITY      1024*1024
#define             POOL_CAPACITY       (TOTAL_CAPACITY/8)

// sMemoryBlockSizeArray: {512, 1024, 2048, 4096, 8192, 16384, 32768, 65536}
class RMemoryManager {

public:

                    RMemoryManager      ();
                    ~RMemoryManager     ();
                    RMemoryManager      (const RMemoryManager&) = delete;

    void*           Allocate            (size_t pSize);
    void            Free                (void* pBlock);

    RMemoryManager& operator=           (const RMemoryManager&) = delete;

    size_t          uCapacity;

private:

    void*           vMemory;

    RFixedPool      pool512;
    RFixedPool      pool1024;
    RFixedPool      pool2048;
    RFixedPool      pool4096;
    RFixedPool      pool8192;
    RFixedPool      pool16384;
    RFixedPool      pool32768;
    RFixedPool      pool65536;
};