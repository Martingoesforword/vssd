#pragma once

class tool_vcmd
{
 
public:
	
	static void v_cmd_comein(vssd_disk & MyVssd, std::wstring &Command); 
	static void vDir(vssd_pan* Top);
	static void vRd(vssd_disk & MyVssd, std::wstring & DirCommand);
	static void vDir(vssd_disk & MyVssd, std::wstring & DirCommand);
	static vssd_folder * v_FindPathForFirst(vssd_disk & MyVssd, std::wstring & DirCommand, tool_path & aPath); 
	static void vCd(vssd_disk & MyVssd, std::wstring & Command);
	static int vMd(vssd_disk & MyVssd, std::wstring & Command); //根据目前文件夹或者根据绝对路径创建
	static void vMove(vssd_disk & MyVssd, std::wstring & Src, std::wstring & Des);
	static void vMove(vssd_disk & MyVssd, std::wstring & Src);
	static void vCd(vssd_pan* Top);
	static void vRd(vssd_disk & MyVssd); 
	static void vRen(vssd_disk & MyVssd, std::wstring & Command);
	static void vRen(vssd_disk & MyVssd, std::wstring & SrcCommand, std::wstring & DisName);
	static void vCls();
	static void v_jump(vssd_disk & MyVssd, std::wstring & JumpTo); 
	static void vSave(vssd_disk & MyVssd, std::wstring & JumpTo);
	static void vLoad(vssd_disk & MyVssd, std::wstring & JumpTo);
	static void vDel(vssd_disk & MyVssd, std::wstring & DelCommand);
	static void vCopy(vssd_disk & MyVssd , std::wstring & Src, std::wstring & Des);
	static void vMklink(vssd_disk & MyVssd, std::wstring & Src, std::wstring & Des); 
	static void vCat(vssd_disk & MyVssd, std::wstring & Rear);
	 
};

