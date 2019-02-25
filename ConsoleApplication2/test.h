#pragma once
template <typename T>
class test
{
	 
public:
	T operator() (T a) { std::cout << "yy"; return a; }
	test(T a) { std::cout << "gg";  }
};

