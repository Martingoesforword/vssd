#include "pch.h"



std::time_t sjh::base_timeable::GetCreateTime()
{
	return CreateTime;
}

sjh::base_timeable::base_timeable()
{
	CreateTime = std::time(0);
}


sjh::base_timeable::~base_timeable()
{
}
