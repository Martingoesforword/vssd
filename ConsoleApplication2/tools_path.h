#pragma once  
#include "pch.h"  
#include "base_serializable.h" 
#include "tools_vssd.h" 
#include "vssd_inode.h" 
namespace sjh {
	class vssd_inode;
	class tools_path :public base_serializable
	{
	private:                         
		int PathTypeCode;
	public:
		//原始构造
		tools_path();
		~tools_path();

		//基类相关
		virtual size_t	Serialize(std::vector<wchar_t> &Byte_Toptable);
		virtual void	DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);
		  
		//Inodes & RealInodes相关
		std::vector<std::wstring>	Inodes;
		std::vector<vssd_inode *>	RealInodes; 
		void	SetInodesByWstring(std::wstring pathString); 
		void	LoadOneSub(const vssd_inode * Inode);
		std::wstring		GetPathWstring() const;
		const vssd_inode *	GetNowPtr() const;
		std::wstring		GetNowWString() ;
		void	DeleteOneSub();
		void	Clear();

		//PathTypeCode相关
		bool IsAbsolutePath() { return PathTypeCode == IS_ABSOLUTE_PATH; }
		bool IsRelativePath() { return PathTypeCode == IS_RELATIVE_PATH; }
		bool IsAbsAndRoot() { return IsAbsolutePath() && Inodes.size() == 1; }
		static const int IS_ABSOLUTE_PATH = 1;
		static const int IS_RELATIVE_PATH = 2;
		int		GetTypeCode();
	};
}