#include "pch.h"
#include "base_timeable.h"

namespace sjh {
	 
	std::time_t base_timeable::GetCreateTime()
	{
		return CreateTime;
	}

	base_timeable::base_timeable()
	{
		CreateTime = std::time(0);
	}

	 
}