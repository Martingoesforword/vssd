#pragma once  
#include "pch.h" 

namespace sjh {
	class VirtualDisk;
	class base_executable
	{
	 
	public:
		//ԭʼ����
		base_executable() {}
		virtual ~base_executable() {};

		//status���
		static const int EXE_ERROR = -1;
		static const int EXE_OK = 0;
		virtual int	Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear) = 0;  
	}; 
}