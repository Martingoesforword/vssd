#pragma once  
#include "pch.h" 
namespace sjh {
	class base_timeable
	{
		std::time_t CreateTime;
	public:
		std::time_t GetCreateTime();
		base_timeable();
		~base_timeable();
	};
}