#pragma once
#include <stdlib.h>
#include "Console.h"

/// <summary>
/// Constant memory buffer
/// </summary>
class HotMemory_ {
private:
	bool inUse_;
	int count_;
	int size_;
	int memorySize_;
public:
	//Const Reference Trick, to make properties read-only
	const bool& inUse;
	const int& count;
	const int& size;
	const int& memorySize;
	const void* elements;

	/// <summary>
	/// Init buffer
	/// </summary>
	/// <param name="memory">pointer of memory</param>
	/// <param name="bytes_">size of memory in bytes</param>
	/// <returns></returns>
	bool Init(void* memory, int bytes_) {
		if (memory == nullptr) {
			Console.LogError("HotMemory: nullreference to memory");
			return false;
		}


		memorySize_ = bytes_;
		elements = memory;
		return true;
	}

	/// <summary>
	/// Append data to buffer
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="element"></param>
	template <class T>
	void Put(T element) {
		if (elements == nullptr) {
			Console.LogError("HotMemory: no memory was set");
		};
		if (count_ >= size_) {
			Console.LogError("HotMemory: memory overflow");
			return;
		}
		*((T*)elements + count_) = element;
		count_++;


	}

	/// <summary>
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <param name="index"></param>
	/// <returns>data from buffer</returns>
	template <class T>
	T Get(int index) {
		return ((T*)elements)[index];
	}

	/// <summary>
	/// If HotMemory is not locked, setup buffer for desired type
	/// </summary>
	/// <typeparam name="T"></typeparam>
	/// <returns>true on succes</returns>
	template <class T>
	bool Use() {
		if (inUse) {
			Console.LogError("HotMemory is already used, free it and then use it again.");
			return false;
		};
		count_ = 0;
		int elementSize = sizeof(T);
		size_ = memorySize / elementSize;
		inUse_ = true;
		return true;
	}

	/// <summary>
	/// Unlocks buffer
	/// </summary>
	void Free() {
		inUse_ = false;
		count_ = 0;
		size_ = 0;
	}

	HotMemory_() : 
		inUse_(false),
		count_(0),
		size_(0),
		memorySize_(0),

		inUse(inUse_),
		count(count_),
		size(size_),
		memorySize(memorySize_)
	{
		inUse_ = false;
		void* ptr = malloc(1024 * 16); //16KB
		Init(ptr, 1024 * 16);
	}

	~HotMemory_() {
		free((void *)elements);
	}

};

static HotMemory_ HotMemory;

