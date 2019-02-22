#pragma once  
#include "pch.h"  
#include "base_serializable.h" 
#include "vssd_time.h" 
namespace sjh { 
	class vssd_content:public base_serializable
	{
	private:
		std::vector<wchar_t>	Content;
		vssd_time				Time;
	public:   
		virtual size_t	Serialize(std::vector<wchar_t>& Byte);
		virtual void	DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);

		void	Add(wchar_t aByte);
		void	SetString(std::wstring aStr);
		std::vector<wchar_t>&	GetContent() { return Content; }
		void	Print();
		size_t	Size();

		//Timeœ‡πÿ 
		std::time_t		GetTime() const;
		void			SetTime(std::time_t) ;
		void			FreshTime();
	};

}