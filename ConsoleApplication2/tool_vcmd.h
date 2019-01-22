#pragma once

static class tool_vcmd
{
 
public:
	
	static void v_cmd_comein(vssd & MyVssd, std::string &Command); 
	static void vDir(vssd_foldertop* Top);
	static void vRd(vssd & MyVssd, std::string & DirCommand);
	static void vDir(vssd & MyVssd, std::string & DirCommand);
	static vssd_folder * v_FindPath(vssd & MyVssd, std::string & DirCommand, tool_path & aPath); 
	static void vCd(vssd & MyVssd, std::string & Command);
	static int vMd(vssd & MyVssd, std::string & Command); //根据目前文件夹或者根据绝对路径创建
	static void vMove(vssd & MyVssd, std::string & Src, std::string & Des);
	static void vMove(vssd & MyVssd, std::string & Src);
	static void vCd(vssd_foldertop* Top);
	static void vRd(vssd & MyVssd); 
	static void vRen(vssd & MyVssd, std::string & Command);
	static void vRen(vssd & MyVssd, std::string & SrcCommand, std::string & DisName);
	static void vCls();
	static void v_jump(vssd & MyVssd, std::string & JumpTo); 
	static void vSave(vssd & MyVssd, std::string & JumpTo);
	static void vLoad(vssd & MyVssd, std::string & JumpTo);
	static void vDel(vssd & MyVssd, std::string & DelCommand);
	static void vCopy(vssd & MyVssd , std::string & Src, std::string & Des);
	static void vMklink(vssd & MyVssd, std::string & Src, std::string & Des);
	 
};

