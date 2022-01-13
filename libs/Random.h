#pragma once
#include <time.h>
#include <stdlib.h>

class Random {
private:

	Random() {
		srand(time(NULL));
	};

	int INumber(int limit, int start = 0) {
		return (rand() % limit) + start;
	}

public:
	static Random& Get() {
		static Random instance;
		return instance;
	}

	static int Number(int limit) {
		return Get().INumber(limit);
	}

	static int Number(int start, int limit) {
		return Get().INumber(limit, start);
	}

	Random(const Random&) = delete;
};