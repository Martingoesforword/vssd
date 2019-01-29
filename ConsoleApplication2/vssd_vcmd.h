#pragma once

class vssd_vcmd
{
 
public:
	
	static void					v_cmd_comein(sjh::vssd_disk & MyVssd, std::wstring &Command); 
	static void					v_jump(sjh::vssd_disk & MyVssd, std::wstring & JumpTo); 
	static bool					v_match(std::wstring & CmdCommand, std::wstring MatchString);
	static sjh::vssd_folder*	v_FindPathForFirst(sjh::vssd_disk & MyVssd, std::wstring  PathCommand, sjh::tool_path & aPath);
	 

};

