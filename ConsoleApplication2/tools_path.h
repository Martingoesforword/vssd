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
		int PathTypeCode = 0;
	public:
		tools_path();
		~tools_path();

		virtual size_t	Serialize(std::vector<wchar_t> &Byte_Toptable);
		virtual void	DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos);


		std::vector<std::wstring> Inodes;
		std::vector<vssd_inode *> RealInodes;

		int					GetTypeCode();
		std::wstring		GetPathWstring();
		vssd_inode *		GetNow();

		void LoadOneSub(vssd_inode * Inode);
		void SetInodesByWstring(std::wstring pathString); //路径字符串到路径对象  
		void DeleteOneSub();
		void Clear();


		bool IsAbsolutePath() { return PathTypeCode == IS_ABSOLUTE_PATH; }
		bool IsRelativePath() { return PathTypeCode == IS_RELATIVE_PATH; }
		static const int IS_ABSOLUTE_PATH = 1;
		static const int IS_RELATIVE_PATH = 2;
	};
}