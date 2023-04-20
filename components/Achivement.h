#pragma once
#include "../include/Object.h"

class Achivement : Object{
	// An achivement is more an observer that plugs into a subjets.
	// When achivement is fullfiled it removes Observers
	// And is set to completed
	// So I need to serialize that..

	// FUUUUCK! The serialisation!

	bool completed = false;
	// name. build in...

	// For this it would be better to make it composition

	// An achivement could be stored as struct.
	// On load up, it could plug to the subjects
	// The subjects, then should be stored globally. And each subject should be unique.
	// That's a problem, i guess.
	// I need to figure out to to make a good system...

	// Got simple idea.

	// Each subject should send some of information.
	//		How subjects would work??

	// Let's make a case study

};