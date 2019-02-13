#include "vssd_optcmd.h"
const std::wstring sjh::vssd_optcmd::GUIDE_SYMBOL = L">";
namespace sjh {  
	 
	vssd_inode * vssd_optcmd::v_FindPathForFirst(VirtualDisk & MyVssd, std::wstring  PathCommand, tools_path &aPath)
	{
		tool::stringtools::Trim(PathCommand);
		tools_path Nowpath = MyVssd.GetNooowPan()->GetNowPath();
		std::wstring pathstring = PathCommand;
		 
		tools_path path;
		path.SetInodesByWstring(pathstring);
		vssd_inode * longNowf = Nowpath.GetNow();

		int flag_tofirstif = 1;
		for (size_t i = 0; i < path.Inodes.size(); i++)
		{
			//说明是磁盘开头，则为绝对路径
			if (flag_tofirstif && path.Inodes[i].length() == 2 && path.Inodes[i].at(1) == ':')
			{
				Nowpath.Clear();
				size_t Result = MyVssd.GetGenius()->FindSelfSubForFirst(path.Inodes[i], 0);
				if (Result != vssd_inode::NOT_FINDED) {
					longNowf = MyVssd.GetGenius()->GetSubInodes()[Result];
				}
				else {
					return nullptr;
				}
				Nowpath.LoadOneSub(longNowf);
				flag_tofirstif = 0;
			}
			else if (path.Inodes.at(i) == L"..")
			{
				if (Nowpath.RealInodes.size() < 2)
				{
					return nullptr;
				}
				else
				{
					Nowpath.DeleteOneSub();
				}

			}
			else if (path.Inodes.at(i) == L".")
			{

			}
			//路径中非'n:' '..' '.'
			else
			{
				size_t Result = longNowf->FindSelfSubForFirst(path.Inodes[i], 0);
				if (Result != vssd_inode::NOT_FINDED) {
					longNowf = longNowf->GetSubInodes()[Result];
				}
				else {
					return nullptr;
				}
				Nowpath.LoadOneSub(longNowf);
				if (longNowf->IsLink() && i + 1 == path.Inodes.size())
				{
					aPath = Nowpath; return longNowf;
				}
				longNowf = longNowf->FindFolderByLink();
			}
		}
		aPath = Nowpath;
		return longNowf;
	}

	vssd_optcmd::vssd_optcmd()
	{
		InitType();
	}
	 

	void vssd_optcmd::v_jump(VirtualDisk & MyVssd, std::wstring & JumpTo)
	{
		vssd_pan* Top = MyVssd.FindPanFromName(JumpTo);
		if (Top) MyVssd.SetNooowPan(Top);
	}

	bool vssd_optcmd::v_match(std::wstring & CmdCommand, std::wstring  MatchString)
	{
		if (CmdCommand.length() >= MatchString.size() &&
			CmdCommand.substr(0, MatchString.size()).compare(MatchString) == IS_SAMESTRING)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void vssd_optcmd::TypeCode_UI_Guider(VirtualDisk & adisk, int GuiderCode)
	{
		std::wcout << adisk.GetNooowPan()->GetNowPathWString() << GUIDE_SYMBOL;
	}
	std::wstring vssd_optcmd::TypeCode_UI_GetCommandString()
	{
		std::string Command;
		while (Command.size() == 0)
		{
			std::getline(std::cin, Command);
		}
		return tool::stringtools::StringToWString(Command);
	}
	int vssd_optcmd::TypeCode_UI(VirtualDisk & adisk)
	{
		int WellRet = 0;
		while (1)
		{ 

			TypeCode_UI_Guider(adisk, 0);
			std::wstring Command = TypeCode_UI_GetCommandString();
			if (sjh::tool::stringtools::WStringMatch(Command, L"exit")) 
			{
				break;
			}
			else
			{
				TypeCode_UI_Explainer(adisk, Command);
				std::cout << "\n";
				WellRet = RET_WELL_OPERATION;
				//处理返回值
			} 
		}
		return RET_WELL_OPERATION;
	}

	 

	void vssd_optcmd::TypeCode_UI_Explainer(VirtualDisk & MyVssd, std::wstring  CmdCommand)
	{

		tool::stringtools::Trim(CmdCommand);
		std::wstring rear;
		std::wstring cmd;
		size_t size1 = 1;
		size_t spacePos = CmdCommand.find(L" ", size1);
		if (spacePos != CmdCommand.npos) {
			rear = CmdCommand.substr(spacePos + 1, CmdCommand.size() - spacePos - 1);
			cmd = CmdCommand.substr(0, CmdCommand.size() - 0);
		}
		else {
			cmd = CmdCommand;
		} 
		std::vector<std::wstring> Rears;
		tool::stringtools::Split(rear, Rears, L" ");
		//分析命令名与命令参数
		if (CmdCommand.length() == 0)
		{
		}
		//dir命令解析
		else if (v_match(CmdCommand, L"dir"))
		{
			vssdDir vDir_task1 ;
			vDir_task1.Execute(MyVssd, Rears);
		}
		//del命令解析
		else if (v_match(CmdCommand, L"del"))
		{
			vssdDel vDel ;
		}
		//save命令解析
		else if (v_match(CmdCommand, L"save"))
		{
			vssdSave vSave ;
		}
		//load命令解析
		else if (v_match(CmdCommand, L"load"))
		{
			vssdLoad vLoad ;
		}
		//mkLink命令解析
		else if (v_match(CmdCommand, L"mklink"))
		{
			size_t size1 = 1;
			size_t spacePos = rear.find(L" ", size1);
			if (spacePos != -1)
			{
				size_t size0 = 0;
				std::wstring rearSrc = rear.substr(size0, spacePos);
				std::wstring reardisName = rear.substr(spacePos + 1, rear.length() - spacePos);
				vssdMklink vMklink ;
			}

		}
		//cd命令解析
		else if (v_match(CmdCommand, L"cd"))
		{
			vssd_pan *Pan = MyVssd.GetNooowPan();
			if (v_match(rear, L"/") || v_match(rear, L"\\"))
			{
				while (Pan->GetNowPath().Inodes.size() > 2) Pan->GetNowPath().DeleteOneSub();
			}
			else
			{
				vssdCd vCd ;
			}
		}
		//rd命令解析
		else if (v_match(CmdCommand, L"rd"))
		{
			vssdRd vRd ;
		}
		//ren命令解析
		else if (v_match(CmdCommand, L"ren"))
		{
			//实现分割函数？？？？？？？？？？
			size_t size1 = 1;
			size_t spacePos = rear.find(L" ", size1);
			if (spacePos != rear.npos)
			{

				std::wstring rearSrc = rear.substr(0, spacePos - 0);
				std::wstring reardisName = rear.substr(spacePos + 1, rear.size() - spacePos - 1);
				vssdRen vRen ;
			}

			//解释:（外框序列数-起始序列数）/序列数量比 = 框内数量 
			//  (-10,60-10)        (-10, (60+10)/10 )
			//-10 0 10 20 30 40 50 60 70 80 90 
			//  9 3  2  3  2  0  3  _  3  2  3

		}
		//copy命令解析
		else if (v_match(CmdCommand, L"copy"))
		{
			size_t size0 = 0;
			size_t spacePos = rear.find(L" ", size0);
			if (spacePos != -1)
			{
				std::wstring rearSrc = rear.substr(size0, spacePos);
				std::wstring rearDes = rear.substr(spacePos + 1, rear.length() - spacePos - 1);
				tool::stringtools::Trim(rearSrc);
				tool::stringtools::Trim(rearDes);
				vssdCopy vCopy ;
			}
		}
		//move命令解析
		else if (v_match(CmdCommand, L"move"))
		{

			size_t spacePos = rear.find(L" ", 0);
			if (spacePos != -1)
			{
				std::wstring rearSrc = rear.substr(0, spacePos);
				std::wstring rearDes = rear.substr(spacePos + 1, rear.length() - spacePos - 1);
				tool::stringtools::Trim(rearSrc);
				tool::stringtools::Trim(rearDes);
				vssdMove vMove ;
			}
			else
			{
				vssdMove vMove ;
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
			vssdCls vCls ;
		}
		//创建文件夹命令解析
		else if (v_match(CmdCommand, L"md"))
		{
			vssdMkdir vMd ;
		}
		//查看文件内容命令解析
		else if (v_match(CmdCommand, L"cat"))
		{

			vssdCat vCat ;
		}
		else {
			std::string a = tool::stringtools::WStringToString(cmd);
			std::cout << "\'" << a << "\' 不是内部或外部命令，也不是可运行的程序\n或批处理文件。";

		}

	}

}