#pragma once
#include <cstddef>
#include <assert.h>
#include "vector.h"

class Observer {
public:
	virtual ~Observer() {};
	virtual void onNotify() = 0;
};


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
