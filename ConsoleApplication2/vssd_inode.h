#pragma once  
#include "pch.h"  
#include "base_contentable.h"  
#include "base_namedable.h"  
#include "base_displayable.h"  
#include "base_serializable.h"  
#include "base_timeable.h"    
#include "tools_vssd.h"    
#include "vssd_manager.h"  
namespace sjh { 
	class vssd_inode :public base_namedable, public  base_displayable, public base_serializable, public base_contentable, public base_timeable
	{
	private:
		unsigned int InodeTypeCode;
		std::vector<vssd_inode *> SubInodes;
		vssd_inode* Father;
	public:
		virtual void Display();
		virtual int  Serialize(std::vector<wchar_t>& aByte);
		virtual void DeSerialize(std::vector<wchar_t>& aByteVssd, int & aPos);

		vssd_inode(std::wstring aName, int aCode);
		~vssd_inode();

		//修改相关 
		void SetFather(vssd_inode * aFather);
		void AddContent(wchar_t aByte);
		void LoadOneSub(vssd_inode * aLinkToSub);
		void UnloadOneSub(vssd_inode * aOffInode);
		void SetContentString(std::wstring aStr);
		void DeleteWholeTree();
		void DeleteOneSub(vssd_inode *aDeletInode);

		//获取相关  
		vssd_inode *				GetFather();
		std::wstring				GetTypeName();
		std::vector<vssd_inode *>&	GetSubInodes();
		int							FindSelfSubForFirst(std::wstring Inode, int StartIndex);
		void						FindSelfSubForAll(std::wstring Inode, std::vector<vssd_inode *> & AllInode);
		vssd_inode *				FindFolderByLink();
		void						PrintContent();
		void						PrintAllSub(vssd_manager & MyVssd, int pram, std::wstring now);


		//检查相关 
		bool IsFile() { return  InodeTypeCode == IS_FILE; }
		bool IsFolder() { return  InodeTypeCode == IS_FOLDER; }
		bool IsLink() { return  InodeTypeCode == IS_LINK; }


		//文件类型相关 
		static const int IS_FILE = 0;
		static const int IS_FOLDER = 1;
		static const int IS_LINK = 2;
		static const std::wstring VssdTypeName[3];

		static const int NOT_FINDED = -1;
	};
}