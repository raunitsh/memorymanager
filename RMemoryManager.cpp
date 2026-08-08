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
    pool16    (GetOffset(vMemory, 0 * POOL_CAPACITY), POOL_CAPACITY, 16),
    pool32    (GetOffset(vMemory, 1 * POOL_CAPACITY), POOL_CAPACITY, 32),
    pool64    (GetOffset(vMemory, 2 * POOL_CAPACITY), POOL_CAPACITY, 64),
    pool128   (GetOffset(vMemory, 3 * POOL_CAPACITY), POOL_CAPACITY, 128)
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
    if      (pSize <= 16)  return pool16.Allocate();
    else if (pSize <= 32)  return pool32.Allocate();
    else if (pSize <= 64)  return pool64.Allocate();
    else if (pSize <= 128) return pool128.Allocate();
    
    else return nullptr;    
}

void
RMemoryManager::Free (void* pBlock)
{
    if (!pBlock) return;
    
    if      (pool16.ContainsPtr(pBlock))  pool16.Free(pBlock);
    else if (pool32.ContainsPtr(pBlock))  pool32.Free(pBlock);
    else if (pool64.ContainsPtr(pBlock))  pool64.Free(pBlock);
    else if (pool128.ContainsPtr(pBlock)) pool128.Free(pBlock);
}