#pragma once  
#include "pch.h" 

namespace sjh {
	class VirtualDisk;
	class base_executable
	{
	protected:
		static const int EXE_ERROR = -1;
		static const int EXE_OK = 0;
		int status;
	public:
		virtual void Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear) = 0;
		int GetStatus() { return status; }
		virtual ~base_executable() {};
	};
	 
}