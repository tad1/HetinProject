#pragma once
#include <cstring>


template <class T>
struct Copyable {
	T value;

	Copyable<T>& operator = (Copyable<T> arg) {
		memcpy(&value, &arg.value, sizeof(T));
		return *this;
	}

	bool operator == (Copyable<T> arg) {
		return this->value == arg.value;//memcmp(&value, &arg.value, sizeof(T));
	}


	//Todo a type that will copy value char[20] instad copying reference
};



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