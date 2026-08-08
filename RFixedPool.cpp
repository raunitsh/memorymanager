#include "./includes/RFixedPool.hpp"

RFixedPool::RFixedPool () 
	:RFixedPool (DEFAULT_CAPACITY) 
{

}

RFixedPool::RFixedPool (size_t pCapacity) 
{
	uCapacity = pCapacity;
  	vMemory = (Block *) malloc (pCapacity);

  	PrivateInitMemory();
}

RFixedPool::RFixedPool (void *pMemory, size_t pTotalSize, size_t pChunkSize) 
{
	vMemory = (Block *)pMemory;
  	vOwnsMemory = false;

	uCapacity = pTotalSize;
	uChunkSize = pChunkSize;

  	PrivateInitMemory ();
}

RFixedPool::~RFixedPool () 
{
	if (vOwnsMemory && vMemory)
		free (vMemory);
}

void *
RFixedPool::Allocate () 
{
	Block *ret = vNextFree;

	if (!vNextFree)
		return nullptr;

	vNextFree = ret->uPrev;

	if (ret->uPrev)
		ret->uPrev->uNext = nullptr;

	ret->uNext = nullptr;
	ret->uPrev = nullptr;

	return ret;
}

void 
RFixedPool::Free (void *pBlock) 
{
	if (!pBlock)
		return;

	Block *incoming = (Block *)pBlock;

	if (!vNextFree) 
	{
		vNextFree = incoming;
		vNextFree->uNext = nullptr;
		vNextFree->uPrev = nullptr;
		return;
	}

	vNextFree->uNext = incoming;

	incoming->uPrev = vNextFree;
	incoming->uNext = nullptr;

	vNextFree = vNextFree->uNext;
}

void 
RFixedPool::PrivateInitMemory () 
{
	if (!vMemory || (uCapacity % uChunkSize != 0))
	{
		vNextFree = 
		vMemEnd =
		vMemory = nullptr;
		return;
	}

	vMemEnd = MOVE_BY(vMemory, uCapacity);

	Block *curr = vMemory;
	Block *prev = nullptr;

	while (curr < vMemEnd) 
	{
		Block *next = MOVE_BY(curr, uChunkSize);

		curr->uPrev = prev;
		curr->uNext = (next < vMemEnd) ? next : nullptr;

		prev = curr;
		curr = next;
	}

	vNextFree = MOVE_BACK_BY (vMemEnd, uChunkSize);
	uSuccess = true;
}

bool 
RFixedPool::ContainsPtr (void *pPtr) const 
{
	return (pPtr >= vMemory && pPtr < vMemEnd);
}