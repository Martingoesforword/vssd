#pragma once  
#include "pch.h"  
#include "vssd_content.h"  
#include "vssd_name.h"  
#include "base_displayable.h"  
#include "base_serializable.h"  
#include "vssd_time.h"    
#include "tools_vssd.h"  

namespace sjh {   
	class tools_path;
	class VirtualDisk;
	class vssd_inode : public  base_displayable, public base_serializable 
	{
	private: 
		unsigned int				InodeTypeCode;
		std::vector<vssd_inode *>	SubInodes;
		vssd_inode*					Father;
		tools_path*					LinkPath;
		vssd_content				Content;
		vssd_name					Name; 
		
	public:
		//原始构造 
		vssd_inode(std::wstring aName, int aCode);  
		~vssd_inode();  
		//基类相关
		virtual size_t	Serialize(std::vector<wchar_t>& aByte);
		virtual void	DeSerialize(std::vector<wchar_t>& aByteVssd, int & aPos);
		virtual void	Display();

		//InodeTypeCode相关 
		static const int	IS_FILE = 0;
		static const int	IS_FOLDER = 1;
		static const int	IS_LINKD = 2;
		static const int	IS_LINKF = 3;
		static const std::wstring	VssdTypeName[4];
		std::wstring	GetTypeName() const;
		void			SetTypeName(int a) { InodeTypeCode = a <= 3 && a >= 0 ? a : 1; };
		bool IsFile()	const	{ return  InodeTypeCode == IS_FILE; }
		bool IsFolder() const	{ return  InodeTypeCode == IS_FOLDER; }
		bool IsLinkD()	const	{ return  InodeTypeCode == IS_LINKD; }
		bool IsLinkF()	const { return  InodeTypeCode == IS_LINKF; }
		//SubInodes相关 
		size_t	SubSize() { return SubInodes.size(); };
		void	LoadOneSub(vssd_inode * aLinkToSub );
		void	UnloadOneSub(vssd_inode * aOffInode);
		void	DeleteAllFile();

		void	DeleteWholeTree(); 
		void	DeleteOneSub(vssd_inode *aDeletInode);
		void	DeleteOneLink(vssd_inode * deletInode);
		const std::vector<vssd_inode *>&		GetSubInodes() const;

		static const int		NOT_FINDED = -1;
		int						FindSelfSubForNext(std::wstring& Inode, size_t StartIndex) const;
		void					FindSelfSubForAll(std::wstring Inode, std::vector<vssd_inode *> & AllInode) const;
		static bool				IsFinded(size_t pos) { return  pos+1 >= 1 ? true : false; }
		static bool				IsNotFinded(size_t pos) { return  pos+1 >= 1 ? false : true; }
		
		void CopyFolder(const VirtualDisk & a,vssd_inode* src);
		 
		//Content相关
		void	AddContent(wchar_t aByte);
		void	SetContentString(std::wstring aStr);
		void	PrintContent();
		std::vector<wchar_t>&	GetContent() { return Content.GetContent(); }
		//Father相关  
		void				SetFather(vssd_inode * aFather) ;
		vssd_inode *		GetFather()  const;
		

		//Print相关
		void	PrintAllSub(int pram, std::wstring now) const;
		void	PrintOTP() const;
		void	PrintHead(std::wstring now) const;
		void	PrintFileInfo();
		void	PrintFoLiInfo();
		
		//LinkPath相关 
		void	SetLinkPath(std::wstring PathWString);
		void	SetLinkPath(tools_path& Path);
		tools_path*	GetLinkPath() { return LinkPath; };
		//Name相关
		void					SetName(std::wstring aName);
		const std::wstring&		GetName() const;
	};
}