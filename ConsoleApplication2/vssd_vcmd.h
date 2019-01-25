#pragma once

class vssd_vcmd
{
 
public:
	
	static void v_cmd_comein(vssd_disk & MyVssd, std::wstring &Command);  
	static vssd_folder * v_FindPathForFirst(vssd_disk & MyVssd, std::wstring & DirCommand, tool_path & aPath);  
	static void v_jump(vssd_disk & MyVssd, std::wstring & JumpTo);  
	 
};

