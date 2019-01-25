#pragma once

class vssd_vcmd
{
 
public:
	
	static void v_cmd_comein(vssd_disk & MyVssd, std::wstring &Command);  
	static vssd_folder * v_FindPathForFirst(vssd_disk & MyVssd, std::wstring & DirCommand, tool_path & aPath);  
	static void v_jump(vssd_disk & MyVssd, std::wstring & JumpTo);

	
	
	static bool v_match(std::wstring & CmdCommand, std::wstring MatchString);

	static std::wstring v_getrear(std::wstring & CmdCommand, std::wstring Command);
	 
};

