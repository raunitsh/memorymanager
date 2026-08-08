#pragma once

#include <stdlib.h>

#define         DEFAULT_CAPACITY            512
#define         CHUNK_SIZE                  32

#define         Byte                        char

struct Block;

#define         MOVE_BY(ptr, bytes)         (Block *)((Byte *)ptr + bytes)
#define         MOVE_BACK_BY(ptr, bytes)    (Block *)((Byte *)ptr - bytes)

struct Block 
{
    Block *     uPrev;
    Block *     uNext;
};

class RFixedPool {

public:
                RFixedPool                  ();
                RFixedPool                  (void *pMemory, size_t pTotalSize, size_t pChunkSize);
                RFixedPool                  (size_t pCapacity);
                ~RFixedPool                 ();
                RFixedPool                  (const RFixedPool&) = delete;

    void *      Allocate                    ();
    void        Free                        (void *pBlock);
    bool        ContainsPtr                 (void *pPtr) const;

    size_t      uCapacity;
    size_t      uChunkSize                  = CHUNK_SIZE;

    RFixedPool& operator=                   (const RFixedPool&) = delete;

    bool        uSuccess                    = false;

private:

    void        PrivateInitMemory           ();

    bool        vOwnsMemory                 = true;
    Block *     vMemory;
    Block *     vMemEnd;
    Block *     vNextFree;
};