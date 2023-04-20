#pragma once

/// <summary>
/// Implementation of vector, similar to vector<T> from standards
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
class Vector {
    static const int alloc_size = 10;
    int count;
    int size;
    T* elements;
private:
    void expand();
public:
    Vector() {
        size = alloc_size;
        elements = new T[alloc_size];
        count = 0;
    }
    ~Vector();

    void push_back(T value);
    void pop_back(T value);
    void get(unsigned int index);
	void remove(T value);
	int find(T value);
	int getCount();
    //void insert(T value, unsigned int index);

    T operator[] (int);
	T* begin() {
		return elements;
	}

	T* end() {
		return elements + count;
	}
};




template<class T>
void Vector<T>::expand()
{
	T* newElements = new T[size + alloc_size];
	for (int i = 0; i < size; i++)
	{
		newElements[i] = elements[i];
	}
	size += alloc_size;
	delete[] elements;
	elements = newElements;
}

template<class T>
Vector<T>::~Vector()
{
	delete[] elements;
}

template<class T>
void Vector<T>::push_back(T value)
{
	if (count >= size) {
		expand();
	}
	elements[count] = value;
	count++;
}

template<class T>
void Vector<T>::pop_back(T value)
{
	count--;
}

template<class T>
void Vector<T>::get(unsigned int index)
{
	return elements[index];
}

template<class T>
int Vector<T>::find(T value) {
	for (int i = 0; i < count; i++)
	{
		if (elements[i] == value) {
			return i;
		}
	}
	return -1;
}

template<class T>
void Vector<T>::remove(T value)
{
	for (int i = 0; i < count; i++)
	{
		if (elements[i] == value) {
			for (int j = i + 1; j < count; j++)
			{
				elements[j - 1] = elements[j];
			}
			i--;
		}
	}
}

template<class T>
int Vector<T>::getCount()
{
	return count;
}

template<class T>
inline T Vector<T>::operator[](int index)
{
	return elements[index];
}