#pragma once  
#include "pch.h" 
#include "base_operater.h"  
#include "tools_path.h"  
#include "vssdCd.h" 
#include "vssdDir.h" 
#include "vssdCat.h" 
#include "vssdCls.h" 
#include "vssdDel.h" 
#include "vssdLoad.h" 
#include "vssdMklink.h" 
#include "vssdMkdir.h" 
#include "vssdMove.h"  
#include "vssdCopy.h" 
#include "vssdRen.h" 
#include "vssdRd.h" 
#include "vssdSave.h" 
#include "vssdSave.h" 

namespace sjh {
	class vssd_inode;
	class VirtualDisk;
	class vssd_optcmd:public base_operater
	{
	private:
		//演示未实现
		int color;
	public: 
		//原始构造
		vssd_optcmd();

		static const std::wstring	GUIDE_SYMBOL;

		//基类相关
		virtual void InitType() { OptType = 1; }
		virtual int ExeInterface(VirtualDisk & MyVssd) { return TypeCode_UI(MyVssd); }

		//TypeCode_UI相关
		static const int RET_WELL_OPERATION = 0;
		static const int RET_ERROR_OPERATION = 1;
		static void				TypeCode_UI_Guider(VirtualDisk & manager, int GuiderCode);
		static std::wstring		TypeCode_UI_GetCommandString();
		static int				TypeCode_UI(VirtualDisk & MyVssd);
		static void				TypeCode_UI_Explainer(VirtualDisk & MyVssd, std::wstring Command);
		 
		//tools相关
		static void					v_jump(VirtualDisk & MyVssd, std::wstring & JumpTo);
		static bool					v_match(std::wstring & CmdCommand, std::wstring MatchString);
		static vssd_inode*			v_FindPathForFirst(VirtualDisk & MyVssd, std::wstring  PathCommand, tools_path & aPath);
		static base_executable *	GetTaskByName(std::wstring Name);
		 
	};
}
