#pragma once
#include "libs/MyString.h"


class Object : public IStringable{
public:
	char* name;
	const char* ToString(){
		return name;
	}

	//TODO: learn about smart pointers
	static void Destroy(Object obj) {
		delete &obj;
	}

	Object(const char* name = "") {
		this->name = (char*)name;
	}

};