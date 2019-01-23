#pragma once

class tool_vcmd
{
 
public:
	
	static void v_cmd_comein(vssd & MyVssd, std::wstring &Command); 
	static void vDir(vssd_foldertop* Top);
	static void vRd(vssd & MyVssd, std::wstring & DirCommand);
	static void vDir(vssd & MyVssd, std::wstring & DirCommand);
	static vssd_folder * v_FindPath(vssd & MyVssd, std::wstring & DirCommand, tool_path & aPath); 
	static void vCd(vssd & MyVssd, std::wstring & Command);
	static int vMd(vssd & MyVssd, std::wstring & Command); //根据目前文件夹或者根据绝对路径创建
	static void vMove(vssd & MyVssd, std::wstring & Src, std::wstring & Des);
	static void vMove(vssd & MyVssd, std::wstring & Src);
	static void vCd(vssd_foldertop* Top);
	static void vRd(vssd & MyVssd); 
	static void vRen(vssd & MyVssd, std::wstring & Command);
	static void vRen(vssd & MyVssd, std::wstring & SrcCommand, std::wstring & DisName);
	static void vCls();
	static void v_jump(vssd & MyVssd, std::wstring & JumpTo); 
	static void vSave(vssd & MyVssd, std::wstring & JumpTo);
	static void vLoad(vssd & MyVssd, std::wstring & JumpTo);
	static void vDel(vssd & MyVssd, std::wstring & DelCommand);
	static void vCopy(vssd & MyVssd , std::wstring & Src, std::wstring & Des);
	static void vMklink(vssd & MyVssd, std::wstring & Src, std::wstring & Des);
	 
};

