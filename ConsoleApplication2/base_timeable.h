#pragma once
#include "pch.h"
class base_timeable
{  
	std::time_t CreateTime;
public:
	std::time_t GetCreateTime();
	base_timeable();
	~base_timeable();
};

