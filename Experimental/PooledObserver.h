#pragma once
#include <cstddef>
#include <assert.h>

class Observer {
public:
	virtual ~Observer() {};
	virtual void onNotify() = 0;
};

class ObserverNode {
	friend class Subject;

public:
	ObserverNode()
		: next_(NULL), previous_(NULL), observer_(NULL)
	{}
	void init(ObserverNode* next, ObserverNode* previous, Observer* observer)
	{
		next_ = next; previous_ = previous;
		observer_ = observer;
	};
	ObserverNode* next_;
	ObserverNode* previous_;
	Observer* observer_;
};

class ObserverNodePool {
public:
	ObserverNodePool();
	ObserverNode* create(ObserverNode* next, ObserverNode* previous, Observer* observer);
	void returnNode(ObserverNode* node);
private:
	ObserverNode* firstAvailable_;
	static const int POOL_SIZE = 100;
	ObserverNode observer_nodes_[POOL_SIZE];
};

class Subject {
	Subject() : head_(NULL), tail_(NULL) {};
public:
	void addObserver(ObserverNode*);
	void removeObserver(ObserverNode*);
protected:
	void notify();
private:
	ObserverNode* head_;
	ObserverNode* tail_;
};
