#pragma once
#include <stdio.h>
#include <cstdarg>
#include <string.h>
#include "../Console.h"

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
		size_t size = snprintf(NULL, 0, "%lf", a);
		if (size == -1) return NULL;
		char* buffer = new char[size + 1];
		snprintf(buffer, size + 1, "%lf", a);
		return buffer;
	}

	template <>
	static const char* ToString(double a) {
		size_t size = snprintf(NULL, 0, "%0.2f", a);
		if (size == -1) return NULL;
		char* buffer = new char[size + 1];
		snprintf(buffer, size + 1, "%0.2f", a);
		return buffer;
	}

	static const char* ToString(int count, ...) {
		va_list args, args2;
		va_start(args, count);
		va_copy(args2, args);

		int buffer_lenght = 0;
		const char* source;
		for (int i = 0; i < count; i++)
		{
			source = va_arg(args, const char*);
			buffer_lenght += strlen(source);
		}
		va_end(args);

		char* buffer = new char[buffer_lenght + 1];
		strcpy(buffer, "");

		va_start(args2, count);
		for (int i = 0; i < count; i++)
		{
			source = va_arg(args2, const char*);
			strcat(buffer, source);
		}
		va_end(args2);
		return buffer;
	
	
	}




	
};
