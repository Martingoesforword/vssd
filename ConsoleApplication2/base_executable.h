#pragma once  
#include "pch.h" 

namespace sjh {
	class VirtualDisk;
	class base_executable
	{
	 
	public:
		//原始构造
		base_executable() {}
		virtual ~base_executable() {};

		//status相关
		static const int EXE_ERROR = -1;
		static const int EXE_OK = 0;
		virtual int	Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear) = 0;  
	}; 
}