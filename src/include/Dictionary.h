#pragma once
#include <string.h>
#include <assert.h>

template <class TKey, class TValue>
struct MapElement {
	TKey key;
	TValue value;
};

//Data structure similar to map
template <class TKey, class TValue>
class Dictionary {
private:
	int alloc_size = 20;
	int size;
	int count;

	MapElement<TKey, TValue>* elements;

	void Expand() {
		size += alloc_size;
		MapElement<TKey, TValue>* temp = new MapElement<TKey, TValue>[size];
		int elementSize = sizeof(TKey) + sizeof(TValue);
		memcpy(temp, elements, elementSize * count);
		delete[] elements;
		elements = temp;
	}
public:
	Dictionary(int allocation_size = 20) {
		alloc_size = allocation_size;
		size = alloc_size;
		elements = new MapElement<TKey, TValue>[alloc_size];
		count = 0;
	}
	~Dictionary() {
		delete[] elements;
	}

	bool ContainsKey(TKey key) {
		for (int i = 0; i < count; i++) {
			if (elements[i].key == key)
				return true;
		}
		return false;
	}

	bool ContainsValue(TValue value) {
		for (int i = 0; i < count; i++) {
			if (elements[i].value == value)
				return true;
		}
		return false;
	}

	void Add(TKey key_, TValue value_) {
		if (!ContainsKey(key_)) {
			if (count >= size) Expand();
			elements[count].key = key_;
			elements[count].value = value_;
			count++;
		}
	}

	void Remove(TKey key) {
		for (int i = 0; i < count; i++) {
			if (elements[i].key == key) {
				if (i < (count - 1)) {
					memcpy(&elements[i], &elements[i + 1], (count - i) - 1);
				}
				count--;
			}
		}
	}

	TValue Get(int index) {
		return elements[index].value;
	}

	void Clear() {
		count = 0;
	}

	int GetCount() {
		return count;
	}

	TValue& operator[] (TKey key) {
		for (int i = 0; i < count; i++) {
			if (elements[i].key == key)
				return elements[i].value;
		}
		//Raise error
		assert(false);
	}
};