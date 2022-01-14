#pragma once
#include <stdio.h>

class Console_ {
public:
	void Log(char* message) {
		printf("%s\n",message);
	}
	void Log(const char* message) {
		printf("%s\n", message);
	}

	void LogError(char* message) {
		printf("Error: %s\n", message);
	}

	void LogError(const char* message) {
		printf("Error: %s\n", message);
	}
} Console;