#pragma once  
#include "pch.h"   
#include "tools_path.h"
#include "vssd_inode.h"
#include "tools_vssd.h" 
namespace sjh {
	
	class vssd_pan :public base_serializable, public base_timeable
	{
	private:
		tools_path NowPath;
		vssd_inode* root;
		
	public:
		vssd_pan(vssd_inode* root, vssd_inode * Genius);
		~vssd_pan();

		virtual void Display();
		virtual int Serialize(std::vector<wchar_t> &Byte_Toptable);
		virtual void DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);

		vssd_inode*	GetRoot();
		tools_path&		GetNowPath();
		vssd_inode*	GetNooowPos();
		 
		std::wstring GetNowPathWString();
		 

	};
}