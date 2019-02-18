#pragma once  
#include "pch.h"  
#include "vssd_time.h"  
#include "vssd_inode.h" 
#include "tools_path.h" 
#include "tools_vssd.h" 

namespace sjh { 
	class vssd_pan :public base_serializable 
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
		void					SetNowPath(tools_path path);
		vssd_inode*				GetNooowPos() const;
		std::wstring			GetNowPathWString() const;
		void	DeleteOneSub();
		

		//Print���
		void	PrintPanInfo();
		
		 

	};
}