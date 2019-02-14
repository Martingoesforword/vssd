#pragma once  
#include "pch.h" 

namespace sjh {
	class VirtualDisk;
	class base_executable
	{
	protected:
		
		int		status;
	public:
		//ԭʼ����
		virtual ~base_executable() {};

		//status���
		static const int EXE_ERROR = -1;
		static const int EXE_OK = 0;
		virtual void	Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear) = 0;
		int				GetStatus() { return status; } 
	}; 
}