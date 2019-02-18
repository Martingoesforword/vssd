#pragma once  
#include "pch.h" 
namespace sjh {
	class vssd_time
	{
	private:
		std::time_t		Time;
	public:
		std::time_t		Get() const;
		void			Fresh();
		vssd_time(); 
	};
}