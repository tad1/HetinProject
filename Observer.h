#pragma once
#include <cstddef>
#include <assert.h>
#include "vector.h"


/// <summary>
/// Implementation of Observer in Observer pattern
/// </summary>
class Observer {
public:
	virtual ~Observer() {};
	virtual void onNotify() = 0;
};

/// <summary>
/// Implementation of subject in Observer pattern
/// </summary>
class Subject {
	Subject(){};
public:
	void addObserver(Observer*);
	void removeObserver(Observer*);
protected:
	void notify();
private:
	Vector<Observer*> observers;
};
