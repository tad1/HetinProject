//Define NULL
#include "Observer.h"

ObserverNodePool::ObserverNodePool(){
	firstAvailable_ = &observer_nodes_[0];

	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		observer_nodes_[i].next_ = &observer_nodes_[i + 1];
	}
	observer_nodes_[POOL_SIZE - 1].next_ = NULL;
}

ObserverNode* ObserverNodePool::create(ObserverNode* next, ObserverNode* previous,Observer* observer) {
	assert(firstAvailable_ != NULL);

	ObserverNode* newNode = firstAvailable_;
	firstAvailable_ = newNode->next_;

	newNode->init(next, previous, observer);
	return newNode;
}

void ObserverNodePool::returnNode(ObserverNode* node)
{
	//if none of observers are available, then update free list
	node->next_ = firstAvailable_;
	firstAvailable_ = node;
}


void Subject::addObserver(ObserverNode* observerNode) {
	//TODO: get observerNode from Pool

	if (head_ == NULL) {
		head_ = observerNode;
	}
	observerNode->previous_ = tail_;
	tail_->next_ = observerNode;
	tail_ = observerNode;
}

void Subject::removeObserver(ObserverNode* observerNode){

	if (head_ == observerNode) {
		head_ = head_->next_;
	}
	else {
		observerNode->previous_->next_ = observerNode->next_;
	}

	if (tail_ == observerNode) {
		tail_ = tail_->previous_;
	}
	else {
		observerNode->next_->previous_ = observerNode->previous_;
	}
	//TODO: return observer from pool
	
}

void Subject::notify()
{
	ObserverNode* observerNode = head_;
	while (observerNode != NULL)
	{
		observerNode->observer_->onNotify();
		observerNode = observerNode->next_;

	}
}


ObserverNodePool observerPool;
