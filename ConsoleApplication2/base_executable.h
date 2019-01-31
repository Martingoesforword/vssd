#pragma once  
#include "pch.h" 

namespace sjh {
	class vssd_manager;
	class base_executable
	{
	protected:
		static const int EXE_ERROR = -1;
		static const int EXE_OK = 0;
	public:
		virtual int Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear) = 0;

		base_executable();
		~base_executable();
	};

}