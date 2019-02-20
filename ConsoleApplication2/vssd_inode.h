#pragma once  
#include "pch.h"  
#include "vssd_content.h"  
#include "vssd_name.h"  
#include "base_displayable.h"  
#include "base_serializable.h"  
#include "vssd_time.h"    
#include "tools_vssd.h"  
#include "tools_path.h"  

namespace sjh {   
	class tools_path;
	class vssd_inode :public vssd_name, public  base_displayable, public base_serializable 
	{
	private:

		unsigned int				InodeTypeCode;
		std::vector<vssd_inode *>	SubInodes;
		vssd_inode*					Father;
		tools_path*					LinkPath;
		vssd_content				Content;
		vssd_name					Name;
	public:
		//ԭʼ����

		vssd_inode(std::wstring aName, int aCode);
		~vssd_inode(); 

		//�������
		virtual size_t	Serialize(std::vector<wchar_t>& aByte);
		virtual void	DeSerialize(std::vector<wchar_t>& aByteVssd, int & aPos);
		virtual void	Display();

		//InodeTypeCode��� 
		static const int	IS_FILE = 0;
		static const int	IS_FOLDER = 1;
		static const int	IS_LINK = 2;
		static const std::wstring	VssdTypeName[3];
		std::wstring	GetTypeName() const;
		bool IsFile()	const	{ return  InodeTypeCode == IS_FILE; }
		bool IsFolder() const	{ return  InodeTypeCode == IS_FOLDER; }
		bool IsLink()	const	{ return  InodeTypeCode == IS_LINK; }

		//SubInodes��� 
		int		SubSize() { return SubInodes.size(); };
		void	LoadOneSub(vssd_inode * aLinkToSub);
		void	UnloadOneSub(vssd_inode * aOffInode); 
		void	DeleteWholeTree(); 
		void	DeleteOneSub(vssd_inode *aDeletInode);
		const std::vector<vssd_inode *>&		GetSubInodes() const;

		static const int		NOT_FINDED = -1;
		int						FindSelfSubForNext(std::wstring& Inode, size_t StartIndex) const;
		void					FindSelfSubForAll(std::wstring Inode, std::vector<vssd_inode *> & AllInode) const;
		static bool				IsFinded(int pos) { return  pos >= 0 ? true : false; }
		static bool				IsNotFinded(int pos) { return  pos >= 0 ? false : true; }
		vssd_inode *			CheckLink() const;
		 
		//Content���
		void	AddContent(wchar_t aByte);
		void	SetContentString(std::wstring aStr);
		void	PrintContent();

		//Father���  
		void				SetFather(vssd_inode * aFather) ;
		vssd_inode *		GetFather()  const;
		

		//Print���
		void	PrintAllSub(int pram, std::wstring now) const;
		void	PrintOTP() const;
		void	PrintHead(std::wstring now) const;
		void	PrintFileInfo();
		void	PrintFoLiInfo();
		
		//LinkPath���
		void	SetLinkPath(std::wstring PathWString);
		void	SetLinkPath(tools_path& Path);

		//Name���
		void					SetName(std::wstring aName);
		const std::wstring&		GetName() const;
	};
}