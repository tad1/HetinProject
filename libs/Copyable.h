#pragma once
#include <cstring>

/// <summary>
/// Structure which allow to copy element instead of passing a reference
/// </summary>
/// <typeparam name="T"></typeparam>
template <class T>
struct Copyable {
	T value;

	Copyable<T>& operator = (Copyable<T> arg) {
		memcpy(&value, &arg.value, sizeof(T));
		return *this;
	}

	bool operator == (Copyable<T> arg) {
		return this->value == arg.value;
	}
};


/// <summary>
/// Structure which allow to copy array of chars instad of copy pointer
/// </summary>
template <int size>
struct CopyableString {
	char c_str[size];

	CopyableString<size>& operator = (CopyableString<size> arg) {
		strcpy(&c_str[0], &arg.c_str[0]);
		return *this;
	}

	CopyableString<size>& operator = (char* arg) {
        strncpy(&c_str[0], arg,size);
		return *this;
	}

	bool operator == (CopyableString<size> arg) {
		return strcmp(c_str, arg.c_str) == 0;//memcmp(&value, &arg.value, sizeof(T));
	}
};