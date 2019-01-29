#include "pch.h" 

//当下文件夹下dir


sjh::vssd_folder * sjh::vssd_vcmd::v_FindPathForFirst(vssd_disk & MyVssd, std::wstring  PathCommand, tool_path &aPath)
{
	tools_vssd::Trim(PathCommand);

	tool_path Nowpath = MyVssd.GetNooowPan()->NowPath;
	std::wstring pathstring = PathCommand;
	

	tool_path path;
	path.WstringToFolders(pathstring); 
	sjh::vssd_folder * longNowf = Nowpath.GetNow();

	int flag_tofirstif = 1;
	for (size_t i = 0; i < path.Folders.size(); i++)
	{
		//说明是磁盘开头，则为绝对路径
		if (flag_tofirstif && path.Folders[i].length() == 2 && path.Folders[i].at(1) == ':')
		{
			Nowpath.Folders.clear();
			Nowpath.RealFolders.clear();
			Nowpath.Folders.push_back(L"");
			Nowpath.SetRealpath(MyVssd.GetGenius(), 0);

			longNowf = Nowpath.GetNow()->FindForFirst(path.Folders[i]);


			if (!longNowf)
			{
				return nullptr;
			}
			Nowpath.AddOne(longNowf);
			while (longNowf->IsLink()) longNowf = longNowf->SubFolders[0];
			flag_tofirstif = 0;
		}
		else if (path.Folders.at(i) == L"..")
		{
			if (Nowpath.RealFolders.size() < 3)
			{
				return nullptr;
			}
			else
			{
				Nowpath.DeleteOneSub();
			}

		}
		else if (path.Folders.at(i) == L".")
		{

		}
		//路径中非'n:' '..' '.'
		else
		{

			longNowf = longNowf->FindForFirst(path.Folders[i]);
			if (!longNowf)
			{

				return nullptr;
			}
			Nowpath.AddOne(longNowf);
			if (longNowf->IsLink() && i + 1 == path.Folders.size())
			{
				aPath = Nowpath; return longNowf;
			}




			while (longNowf->IsLink()) longNowf = longNowf->SubFolders[0];
		}

	}

	aPath = Nowpath; 
	return longNowf;


}

void sjh::vssd_vcmd::v_jump(vssd_disk & MyVssd, std::wstring & JumpTo)
{
	sjh::vssd_pan* Top = MyVssd.FindPanFromName(JumpTo);
	MyVssd.SetNooowPan(Top);
}

bool sjh::vssd_vcmd::v_match(std::wstring & CmdCommand, std::wstring  MatchString)
{
	if (CmdCommand.length() >= MatchString.size() && CmdCommand.substr(0, MatchString.size()).compare(MatchString) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
std::wstring sjh::vssd_vcmd::v_getrear_trim(std::wstring & CmdCommand, std::wstring  Command)
{
	std::wstring rear = CmdCommand.substr(Command.size(), CmdCommand.size() - Command.size());
	tools_vssd::Trim(rear);
	return rear;
}

void sjh::vssd_vcmd::v_cmd_comein(vssd_disk & MyVssd, std::wstring & CmdCommand)
{
	 
	tools_vssd::Trim(CmdCommand); 
	std::wstring rear; 
	std::wstring cmd;
	int spacePos = CmdCommand.find(L" ", 1);
	if (spacePos != CmdCommand.npos) {
		rear = CmdCommand.substr(spacePos+1, CmdCommand.size()-spacePos-1);
		cmd = CmdCommand.substr(0, CmdCommand.size() - 0);
	}
	else {
		cmd = CmdCommand;
	}
	//分析命令名与命令参数
	if (CmdCommand.length() == 0)
	{
	}
	//dir命令解析
	else if (v_match(CmdCommand, L"dir"))
	{  
		sjh::vssdDir::vDir(MyVssd, rear); 
	}
	//del命令解析
	else if (v_match(CmdCommand, L"del"))
	{  
		sjh::vssdDel::vDel(MyVssd, rear);  
	}
	//save命令解析
	else if (v_match(CmdCommand, L"save"))
	{   
		sjh::vssdSave::vSave(MyVssd, rear); 
	}
	//load命令解析
	else if (v_match(CmdCommand, L"load"))
	{   
		sjh::vssdLoad::vLoad(MyVssd, rear); 
	}
	//mkLink命令解析
	else if (v_match(CmdCommand, L"mklink"))
	{  
		int spacePos = rear.find(L" ", 1);
		if (spacePos != -1)
		{ 
			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring reardisName = rear.substr(spacePos + 1, rear.length() - spacePos); 
			sjh::vssdMklink::vMklink(MyVssd, rearSrc, reardisName); 
		}

	}
	//cd命令解析
	else if (v_match(CmdCommand, L"cd"))
	{   
		sjh::vssd_pan *Pan = MyVssd.GetNooowPan(); 
		if (v_match(rear, L"/") || v_match(rear, L"\\"))
		{
			while (Pan->NowPath.Folders.size() > 2) Pan->NowPath.DeleteOneSub();
		}
		else
		{
			sjh::vssdCd::vCd(MyVssd, rear);
		}
	}
	//rd命令解析
	else if (v_match(CmdCommand, L"rd"))
	{  
		sjh::vssdRd::vRd(MyVssd, rear); 
	}
	//ren命令解析
	else if (v_match(CmdCommand, L"ren"))
	{ 
		//实现分割函数？？？？？？？？？？
		int spacePos = rear.find(L" ", 1);
		if (spacePos != rear.npos)
		{ 
			std::wstring rearSrc = rear.substr(0, spacePos-0);
			std::wstring reardisName = rear.substr(spacePos + 1, rear.size() - spacePos-1); 
			sjh::vssdRen::vRen(MyVssd, rearSrc, reardisName); 
		} 

		//解释:（外框序列数-起始序列数）/序列数量比 = 框内数量 
		//  (-10,60-10)        (-10, (60+10)/10 )
		//-10 0 10 20 30 40 50 60 70 80 90 
		//  9 3  2  3  2  0  3  _  3  2  3

	}
	//copy命令解析
	else if (v_match(CmdCommand, L"copy"))
	{ 
		int spacePos = rear.find(L" ", 0);
		if (spacePos != -1)
		{ 
			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring rearDes = rear.substr(spacePos + 1, rear.length() - spacePos - 1);
			tools_vssd::Trim(rearSrc);
			tools_vssd::Trim(rearDes);
			sjh::vssdCopy::vCopy(MyVssd, rearSrc, rearDes);
		} 
	}
	//move命令解析
	else if (v_match(CmdCommand, L"move"))
	{
		
		int spacePos = rear.find(L" ", 0);
		if (spacePos != -1)
		{ 
			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring rearDes = rear.substr(spacePos + 1, rear.length() - spacePos - 1);
			tools_vssd::Trim(rearSrc);
			tools_vssd::Trim(rearDes);
			sjh::vssdMove::vMove(MyVssd, rearSrc, rearDes);
		}
		else
		{ 
			sjh::vssdMove::vMove(MyVssd, rear);
		}
		 
	}
	//跳转盘命令解析
	else if (CmdCommand.length() == 2 && CmdCommand.at(1) == ':')
	{  
		v_jump(MyVssd, CmdCommand);
	}
	//清屏命令解析
	else if (v_match(CmdCommand, L"cls"))
	{
		sjh::vssdCls::vCls();
	}
	//创建文件夹命令解析
	else if (v_match(CmdCommand, L"mkdir"))
	{  
		sjh::vssdMd::vMd(MyVssd, rear);
	}
	//查看文件内容命令解析
	else if (v_match(CmdCommand, L"cat"))
	{  
		sjh::vssdCat::vCat(MyVssd, rear); 
	}
	else { 
	std::string a =  sjh::tools_vssd::WStringToString(cmd);
	std::cout << "\'" << a << "\' 不是内部或外部命令，也不是可运行的程序\n或批处理文件。";
		 
	}

}

