//#include <stdio.h>
//#include <assert.h>
//#include "../libs/Copyable.h"
//
//
////test1
//Copyable<int> a = {5};
//Copyable<int> b = {5};
//assert(a == b);
//
//b = Copyable<int> {6};
//a = b;
//assert(a.value == 6);
//
//Copyable<char[20]> str1 = { "asdf" };
//Copyable<char[20]> str2 = { "asdf" };
//assert(str1 == str2);
//str2.value = Copyable<char[20]> { "feijfejief" };
//str1 = str2;
//assert(str1.value == "feijfejief");