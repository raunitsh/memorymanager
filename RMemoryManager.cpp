#include "./includes/RMemoryManager.hpp"

static inline void*
GetOffset (void* buffer, size_t offset) 
{
    return (void*)((char*)buffer + offset);
}

RMemoryManager::RMemoryManager(size_t pTotalCapacity)
    : 
    uCapacity   (pTotalCapacity),
    vMemory     (malloc(pTotalCapacity)),      
    pool16      (GetOffset(vMemory, 0),                                 (size_t)(pTotalCapacity * 0.15),                    16),             
    pool32      (GetOffset(vMemory, (size_t)(pTotalCapacity * 0.15)),   (size_t)(pTotalCapacity * 0.25),                    32),          
    pool64      (GetOffset(vMemory, (size_t)(pTotalCapacity * 0.40)),   (size_t)(pTotalCapacity * 0.25),                    64),
    pool128     (GetOffset(vMemory, (size_t)(pTotalCapacity * 0.65)),   (size_t)(pTotalCapacity * 0.20),                    128),          
    pool256     (GetOffset(vMemory, (size_t)(pTotalCapacity * 0.85)),   pTotalCapacity - (size_t)(pTotalCapacity * 0.85),   256)
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
    else if (pSize <= 256) return pool256.Allocate();
    
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
    else if (pool256.ContainsPtr(pBlock)) pool256.Free(pBlock);
}