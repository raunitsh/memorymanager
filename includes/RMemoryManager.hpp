#include "./RFixedPool.hpp"

#define             TOTAL_CAPACITY      1024*1024
#define             POOL_CAPACITY       (TOTAL_CAPACITY/4)

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

    RFixedPool      pool16;
    RFixedPool      pool32;
    RFixedPool      pool64;
    RFixedPool      pool128;
};