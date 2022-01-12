#pragma once
#include <stdio.h>


class IStringable {
public:
	virtual ~IStringable() {};
	virtual const char* ToString() = 0;
};

class String {

private:
	const char* string;
public:
	String(const char* str) : string(str) {};
	operator const char* () {
		return string;
	}

	String& operator = (String str) {
		String* temp = new String(str);
		return *temp;
	}

	template <class T>
	static const char* ToString(T a) {
		return "Cannot convert to string.";
	}

	template <>
	static const char* ToString(int a) {
		size_t size = snprintf(NULL, 0, "%d", a);
		char* buffer = new char[size + 1];
		snprintf(buffer, size + 1, "%d", a);
		return buffer;
	}

	template <>
	static const char* ToString(float a) {
		size_t size = snprintf(NULL, 0, "%f", a);
		if (size == -1) return NULL;
		char* buffer = new char[size + 1];
		snprintf(buffer, size + 1, "%f", a);
		return buffer;
	}
};
