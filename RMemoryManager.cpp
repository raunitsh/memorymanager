#include "./includes/RMemoryManager.hpp"

static inline void*
GetOffset (void* buffer, size_t offset) 
{
    return (void*)((char*)buffer + offset);
}

RMemoryManager::RMemoryManager ()
    : 
    uCapacity (TOTAL_CAPACITY),
    vMemory   (malloc (uCapacity)),      
    pool16    (GetOffset(vMemory, 0 * SLICE_SIZE),  2 * SLICE_SIZE, 16),
    pool32    (GetOffset(vMemory, 2 * SLICE_SIZE),  2 * SLICE_SIZE, 32),
    pool64    (GetOffset(vMemory, 4 * SLICE_SIZE),  2 * SLICE_SIZE, 64),
    pool128   (GetOffset(vMemory, 6 * SLICE_SIZE),  1 * SLICE_SIZE, 128),
    pool256   (GetOffset(vMemory, 7 * SLICE_SIZE),  1 * SLICE_SIZE, 256),
    pool512   (GetOffset(vMemory, 8 * SLICE_SIZE),  1 * SLICE_SIZE, 512),
    pool1024  (GetOffset(vMemory, 9 * SLICE_SIZE),  1 * SLICE_SIZE, 1024),
    pool2048  (GetOffset(vMemory, 10 * SLICE_SIZE), 1 * SLICE_SIZE, 2048),
    pool4096  (GetOffset(vMemory, 11 * SLICE_SIZE), 1 * SLICE_SIZE, 4096),
    pool8192  (GetOffset(vMemory, 12 * SLICE_SIZE), 1 * SLICE_SIZE, 8192),
    pool16384 (GetOffset(vMemory, 13 * SLICE_SIZE), 1 * SLICE_SIZE, 16384),
    pool32768 (GetOffset(vMemory, 14 * SLICE_SIZE), 1 * SLICE_SIZE, 32768),
    pool65536 (GetOffset(vMemory, 15 * SLICE_SIZE), 1 * SLICE_SIZE, 65536)
{

}

RMemoryManager::~RMemoryManager ()
{
    if (vMemory)
    {
        free (vMemory);    
        vMemory = nullptr;
    }
}

void*
RMemoryManager::Allocate (size_t pSize)
{
    if      (pSize <= 16)    return pool16.Allocate();
    else if (pSize <= 32)    return pool32.Allocate();
    else if (pSize <= 64)    return pool64.Allocate();
    else if (pSize <= 128)   return pool128.Allocate();
    else if (pSize <= 256)   return pool256.Allocate();
    else if (pSize <= 512)   return pool512.Allocate();
    else if (pSize <= 1024)  return pool1024.Allocate();
    else if (pSize <= 2048)  return pool2048.Allocate();
    else if (pSize <= 4096)  return pool4096.Allocate();
    else if (pSize <= 8192)  return pool8192.Allocate();
    else if (pSize <= 16384) return pool16384.Allocate();
    else if (pSize <= 32768) return pool32768.Allocate();
    else if (pSize <= 65536) return pool65536.Allocate();
    
    else return nullptr;    
}

void
RMemoryManager::Free (void* pBlock)
{
    if (!pBlock) return;
    
    if      (pool16.ContainsPtr(pBlock))    pool16.Free(pBlock);
    else if (pool32.ContainsPtr(pBlock))    pool32.Free(pBlock);
    else if (pool64.ContainsPtr(pBlock))    pool64.Free(pBlock);
    else if (pool128.ContainsPtr(pBlock))   pool128.Free(pBlock);
    else if (pool256.ContainsPtr(pBlock))   pool256.Free(pBlock);
    else if (pool512.ContainsPtr(pBlock))   pool512.Free(pBlock);
    else if (pool1024.ContainsPtr(pBlock))  pool1024.Free(pBlock);
    else if (pool2048.ContainsPtr(pBlock))  pool2048.Free(pBlock);
    else if (pool4096.ContainsPtr(pBlock))  pool4096.Free(pBlock);
    else if (pool8192.ContainsPtr(pBlock))  pool8192.Free(pBlock);
    else if (pool16384.ContainsPtr(pBlock)) pool16384.Free(pBlock);
    else if (pool32768.ContainsPtr(pBlock)) pool32768.Free(pBlock);
    else if (pool65536.ContainsPtr(pBlock)) pool65536.Free(pBlock);
}