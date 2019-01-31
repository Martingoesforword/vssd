#pragma once  
#include "pch.h"  
#include "vssd_inode.h" 
#include "tools_path.h" 
#include "vssd_disk.h" 
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
namespace sjh {
	class vssd_vcmd
	{
		static const std::wstring GUIDESYMBOL;
	public:
		 
		static void					TypeCode_UI_Guider(vssd_disk & manager, int GuiderCode);
		static std::wstring			TypeCode_UI_GetCommandString();
		static void					TypeCode_UI(vssd_disk & MyVssd);
		static void					TypeCode_UI_Explainr(vssd_disk & MyVssd, std::wstring Command);
		static void					v_jump(vssd_disk & MyVssd, std::wstring & JumpTo);
		static bool					v_match(std::wstring & CmdCommand, std::wstring MatchString);
		static vssd_inode*			v_FindPathForFirst(vssd_disk & MyVssd, std::wstring  PathCommand, tools_path & aPath);

	};
}
const std::wstring sjh::vssd_vcmd::GUIDESYMBOL = L">";