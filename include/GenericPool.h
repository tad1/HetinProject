#pragma once

/// <summary>
/// Generic object pool pattern
/// </summary>
/// <typeparam name="TObject"></typeparam>
template <class TObject, int size>
class GenericPool {
public:
	static const int POOL_SIZE = size;
	TObject pool[POOL_SIZE];
	bool inUse[POOL_SIZE];
};


template <class TObject>
class FixedObjectPool {
private:
	size_t size;
	size_t count;
	TObject* mem;
	bool* inUse;
	size_t objectSize;

	void Alloc() {
		if (mem != nullptr) {
			free(mem);
			free(inUse);
		}
		mem = (TObject*)malloc(size * objectSize);
		inUse = (bool*)calloc(false, size * sizeof(bool));
		if (mem == nullptr) {
			size = 0;
			if (inUse != nullptr) {
				free(inUse);
			}
		}
		else if (inUse == nullptr) {
			free(mem);
			size = 0;
		}

	}

public:
	FixedObjectPool(int size) {
		this->size = size;
		objectSize = sizeof(TObject);
		mem = nullptr;
		count = 0;
		Alloc();
	}

	size_t GetFirstFree() {
		for (int i = 0; i < size; i++) {
			if (inUse[i] == false) {
				return i;
			}
		}
		return size;
	}

	//TObject* create(TObject&& object) {
	//	size_t freeIndex = GetFirstFree();
	//	if (freeIndex == size) return nullptr;

	//	//Perfect forwarding
	//	TObject* ptr = ::operator new(mem + freeIndex) TObject(std::forward<TObject>(object));
	//	count++;
	//	return ptr;
	//}

	TObject* create() {
		size_t freeIndex = GetFirstFree();
		if (freeIndex == size) return nullptr;

		//Perfect forwarding
		//TObject* ptr = ::operator new(mem + freeIndex) TObject();
		TObject* ptr = mem + freeIndex;
		count++;
		return ptr;
	}

	void destory(TObject* object) {
		if (object == nullptr) return;
		size_t index = object - mem;
		inUse[i] = false;
		count--;
	}


	~FixedObjectPool() {
		deleteAll();
	}

	void deleteAll() {
		free(mem);
		mem = nullptr;
	}
};