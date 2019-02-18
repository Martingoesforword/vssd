#pragma once  
#include "pch.h"  
#include "vssd_time.h"  
namespace sjh { 
	class vssd_content
	{
	private:
		std::vector<wchar_t>	Content;
		vssd_time				Time;
	public:   
		void	Add(wchar_t aByte);
		void	SetString(std::wstring aStr);
		void	Print();
		size_t	Size();

		//Timeœ‡πÿ 
		std::time_t		GetTime() const;
		void			FreshTime();
	};

}