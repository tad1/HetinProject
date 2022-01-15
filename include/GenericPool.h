#pragma once

/// <summary>
/// Generic object pool pattern
/// </summary>
/// <typeparam name="TObject"></typeparam>
template <class TObject, int size>
class GenericPool {
public:
	static const int POOL_SIZE = size;
	TObject pool[POOL_SIZE];
	bool inUse[POOL_SIZE];
};