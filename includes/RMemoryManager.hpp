#include "./RFixedPool.hpp"

class RMemoryManager {

    public:

                RMemoryManager      (size_t pCapacity = 10240);
                ~RMemoryManager     ();


    void*       Allocate            (size_t pSize);
    void        Free                (void* pBlock);

    size_t      uCapacity;

    private:

    void*       vMemory;

    RFixedPool  pool16;
    RFixedPool  pool32;
    RFixedPool  pool64;
    RFixedPool  pool128;
    RFixedPool  pool256;
};