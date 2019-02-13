#pragma once  
#include "pch.h" 
namespace sjh {
	class base_serializable
	{
	public:
		virtual size_t	Serialize(std::vector<wchar_t>& Byte) = 0;
		virtual void	DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos) = 0;
		 
	};

}