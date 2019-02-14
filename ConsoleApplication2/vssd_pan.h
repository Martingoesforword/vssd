#pragma once  
#include "pch.h"  
#include "base_timeable.h"  
#include "vssd_inode.h" 
#include "tools_path.h" 
#include "tools_vssd.h" 

namespace sjh { 
	class vssd_pan :public base_serializable, public base_timeable
	{
	private:
		tools_path	NowPath;
		vssd_inode*	root; 
	public:
		//ԭʼ����
		vssd_pan(vssd_inode* root, vssd_inode * Genius);
		~vssd_pan();
		//�������
		virtual void	Display();
		virtual size_t	Serialize(std::vector<wchar_t> &Byte_Toptable);
		virtual void	DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);

		//root���
		vssd_inode*		GetRoot();

		//NowPath���
		tools_path&		GetNowPath();
		vssd_inode*		GetNooowPos();
		std::wstring	GetNowPathWString();

		//Print���
		void	PrintPanInfo();
		
		 

	};
}