#pragma once  
#include "pch.h"  
#include "base_contentable.h"  
#include "base_namedable.h"  
#include "base_displayable.h"  
#include "base_serializable.h"  
#include "base_timeable.h"    
#include "tools_vssd.h"  
#include "tools_path.h"  

namespace sjh {   
	class vssd_inode :public base_namedable, public  base_displayable, public base_serializable, public base_contentable, public base_timeable
	{
	private:
		unsigned int				InodeTypeCode;
		std::vector<vssd_inode *>	SubInodes;
		vssd_inode*					Father;
		tools_path					LinkPath;

	public:
		//原始构造
		vssd_inode(std::wstring aName, int aCode);
		~vssd_inode(); 

		//基类相关
		virtual size_t	Serialize(std::vector<wchar_t>& aByte);
		virtual void	DeSerialize(std::vector<wchar_t>& aByteVssd, int & aPos);
		virtual void	Display();

		//InodeTypeCode相关 
		static const int IS_FILE = 0;
		static const int IS_FOLDER = 1;
		static const int IS_LINK = 2;
		static const std::wstring VssdTypeName[3];
		std::wstring				GetTypeName();
		bool IsFile() { return  InodeTypeCode == IS_FILE; }
		bool IsFolder() { return  InodeTypeCode == IS_FOLDER; }
		bool IsLink() { return  InodeTypeCode == IS_LINK; }

		//SubInodes相关   
		void	LoadOneSub(vssd_inode * aLinkToSub);
		void	UnloadOneSub(vssd_inode * aOffInode); 
		void	DeleteWholeTree(); 
		void	DeleteOneSub(vssd_inode *aDeletInode);
		std::vector<vssd_inode *>&		GetSubInodes();

		static const int NOT_FINDED = -1;
		size_t			FindSelfSubForFirst(std::wstring Inode, size_t StartIndex);
		void			FindSelfSubForAll(std::wstring Inode, std::vector<vssd_inode *> & AllInode);
		vssd_inode *	FindFolderByLink();
		

		//Content相关
		void	AddContent(wchar_t aByte);
		void	SetContentString(std::wstring aStr);
		void	PrintContent();

		//Father相关  
		void			SetFather(vssd_inode * aFather);
		vssd_inode *	GetFather(); 
		

		//Print相关
		void	PrintAllSub(int pram, std::wstring now);
		void	PrintOTP();
		void	PrintHead(std::wstring now);
		void	PrintFileInfo();
		void	PrintFoLiInfo(); 
		
		//LinkPath相关
		void	SetLinkPath(std::wstring PathWString);
		void	SetLinkPath(tools_path& Path);
	};
}