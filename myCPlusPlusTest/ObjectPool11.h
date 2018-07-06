#ifndef _H_OBJECTPOOL11_H_
#define _H_OBJECTPOOL11_H_

#include <cstddef>
#include <queue>
#include <stdexcept>
#include <memory>

template < typename T >
class ObjectPool11
{
public:
	// Creates an object pool with chunkSize objects.
	// Whenever the object pool runs out of objects, chunkSize
	// more objects will be added to the pool. The pool only grows:
	// objects are never removed from the pool (freed), until
	// the pool is destroyed.
	//
	// Throws invalid_argument if chunkSize is 0.
	// Throws bad_alloc if allocation fails.
	ObjectPool11(size_t chunkSize = kDefaultChunkSize)
	{
		if (chunkSize == 0)
		{
			throw std::invalid_argument("chunk size must be positive");
		}

		mChunkSize = chunkSize;

		// Create mChunkSize objects to start.
		allocateChunk();
	}

	ObjectPool11(const ObjectPool11<T>& src) = delete;
	ObjectPool11<T> operator=(const ObjectPool11<T>& src) = delete;

	// The type of smart pointer returned by acquireObject().
	using Object = std::shared_ptr<T>;

	// Reserves an object for use.
	Object acquireObject()
	{
		if (mFreeList.empty())
		{
			allocateChunk();
		}

		// Move next free object from the queue to a local unique_ptr.
		std::unique_ptr<T> obj = std::move(mFreeList.front());
		mFreeList.pop();

		//Convert the object pointer to an Object (a shared_ptr with a custom deleter).
		Object smartObject = (obj.release(), [this](T* t) {
			// The custom deleter doesn't actually deallocate the 
			// memory, but simply puts the object back on the free list.
			mFreeList.push(std::unique_ptr<T>(t));
		});

		return smartObject;
	}

private:

	std::queue<std::unique_ptr<T>> mFreeList;
	size_t mChunkSize;
	static const size_t kDefaultChunkSize = 10;


	// Allocates mChunkSize new objexts and adds them to mFeeList.
	void allocateChunk( )
	{
		for (size_t i = 0; i < mChunkSize; ++i)
		{
			mFreeList.emplace(std::make_unique<T>());
		}
	}
};

#endif // _H_OBJECTPOOL11_H_
