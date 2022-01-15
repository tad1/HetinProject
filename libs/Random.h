#pragma once
#include <time.h>
#include <stdlib.h>


/// <summary>
/// Singleton for pseudo-random generator
/// </summary>
class Random {
private:

	Random() {
		srand(time(NULL));
	};

	
	int INumber(int limit, int start = 0) {
		return (rand() % limit) + start;
	}

public:

	/// <returns>Singleton instance</returns>
	static Random& Get() {
		static Random instance;
		return instance;
	}

	/// <returns>Exclusive Random number</returns>
	static int Number(int limit) {
		return Get().INumber(limit);
	}

	/// <returns>Exclusive Random number</returns>
	static int Number(int start, int limit) {
		return Get().INumber(limit, start);
	}

	//Prevents to copy instance
	Random(const Random&) = delete;
};