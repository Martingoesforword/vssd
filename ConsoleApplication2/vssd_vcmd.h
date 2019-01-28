#pragma once

class vssd_vcmd
{
 
public:
	
	static void v_cmd_comein(sjh::vssd_disk & MyVssd, std::wstring &Command);
	static sjh::vssd_folder * v_FindPathForFirst(sjh::vssd_disk & MyVssd, std::wstring & DirCommand, sjh::tool_path & aPath);
	static void v_jump(sjh::vssd_disk & MyVssd, std::wstring & JumpTo);
	 
	
	static bool v_match(std::wstring & CmdCommand, std::wstring MatchString);

	static std::wstring v_getrear_trim(std::wstring & CmdCommand, std::wstring Command);
	 


};

