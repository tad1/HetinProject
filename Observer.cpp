//Define NULL
#include "Observer.h"



void Subject::addObserver(Observer* observer) {
	observers.push_back(observer);
}

void Subject::removeObserver(Observer* observer){
	observers.remove(observer);
	
}

void Subject::notify()
{
	for (int i = 0; i < observers.getCount(); i++)
	{
		observers[i]->onNotify();
	}
}

