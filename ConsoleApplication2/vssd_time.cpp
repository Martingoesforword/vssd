#include "pch.h"
#include "vssd_time.h"

namespace sjh {
	 
	std::time_t vssd_time::Get() const
	{
		return Time;
	}

	void vssd_time::Set(std::time_t	aTime)
	{
		Time = aTime;
	}

	void vssd_time::Fresh()
	{
		
		Time = std::time(0);
	}

	vssd_time::vssd_time():Time(std::time(0))
	{ 
	} 
}