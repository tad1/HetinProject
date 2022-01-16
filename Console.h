#pragma once
#include <stdio.h>

/// <summary>
/// API that allow to easly print message
/// </summary>
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
};
static Console_ Console;