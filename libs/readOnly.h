#pragma once
template <class T, class Class>
class readOnly {
	//friend class Class;
private:
	T data;
	T operator=(const T& arg) {
		data = arg;
		return data;
	}
public:
	operator const T& () const { return data; }

};