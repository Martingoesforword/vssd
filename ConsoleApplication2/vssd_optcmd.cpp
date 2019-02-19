#include "pch.h"  
#include "vssd_optcmd.h"
const std::wstring sjh::vssd_optcmd::GUIDE_SYMBOL = L">";
namespace sjh {  
	 
	vssd_inode * vssd_optcmd::v_FindPathForFirst(const VirtualDisk & MyVssd, std::wstring  PathCommand, tools_path &aPath)
	{
		tool::string::Trim(PathCommand);
		//Nowpath  copy and swap策略 
		tools_path Nowpath = MyVssd.GetNooowPan()->GetNowPath();
		std::wstring pathstring = PathCommand;
		 
		tools_path path;
		path.SetInodesByWstring(pathstring);

		const vssd_inode * longNowf = Nowpath.GetNowPtr();

		int flag_tofirstif = 1;
		for (size_t i = 0; i < path.Inodes.size(); i++)
		{
			//说明是磁盘开头，则为绝对路径
			if (flag_tofirstif && path.Inodes[i].length() == 2 && path.Inodes[i].at(1) == ':')
			{
				Nowpath.Clear();
				size_t Result = MyVssd.GetGenius()->FindSelfSubForNext(path.Inodes[i], 0);
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
			else
			{
				size_t Result = longNowf->FindSelfSubForNext(path.Inodes[i], 0);
				if (Result != vssd_inode::NOT_FINDED) {
					longNowf = longNowf->GetSubInodes()[Result];
				}
				else {
					return nullptr;
				}
				Nowpath.LoadOneSub(longNowf);
				if (longNowf->IsLink() && (i + 1) == path.Inodes.size())
				{
					aPath = Nowpath; return (vssd_inode *)longNowf;
				}
				longNowf = longNowf->FindFolderByLink();
			}
		}
		aPath = Nowpath;
		return const_cast< vssd_inode *>(longNowf);
	}

	vssd_optcmd::vssd_optcmd()
	{
		InitType();
	}
	 

	void vssd_optcmd::v_jump(VirtualDisk & MyVssd, const std::wstring & JumpTo)
	{
		vssd_pan* Top = MyVssd.FindPanFromName(JumpTo);
		if (nullptr != Top) MyVssd.SetNooowPan(Top);
	}

	bool vssd_optcmd::v_match(const std::wstring & CmdCommand, const std::wstring&  MatchString)
	{
		return CmdCommand.compare(MatchString) == 0;
	}

	void vssd_optcmd::TypeCode_UI_Guider(const VirtualDisk & adisk, int GuiderCode)
	{
		std::wstring a = adisk.GetNooowPan()->GetNowPathWString();
		std::wcout << a << GUIDE_SYMBOL;
	}
	const std::wstring vssd_optcmd::TypeCode_UI_GetCommandString()
	{
		std::string Command;
		while (Command.size() == 0)
		{
			std::getline(std::cin, Command);
		}
		return tool::string::StringToWString(Command);
	}
	int vssd_optcmd::TypeCode_UI(VirtualDisk & adisk)
	{
		int WellRet = 0;
		while (1)
		{ 

			TypeCode_UI_Guider(adisk, 0);
			std::wstring Command = TypeCode_UI_GetCommandString();
			tool::string::Trim(Command);
			if (tool::string::WStringMatch(Command, L"exit")) 
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

	 

	void vssd_optcmd::TypeCode_UI_Explainer(VirtualDisk & MyVssd,const std::wstring&  CmdCommand)
	{
		if (CmdCommand.length() == 0) {} 
		std::vector<std::wstring>	Rears;
		tool::string::Split(CmdCommand, Rears, L" ");
		//分析命令名与命令参数
		
		if (0 != Rears.size())
		{
			base_executable *exe = GetTaskByName(Rears[0]);
			if (exe != nullptr)
			{
				exe->Execute(MyVssd, Rears); 
				delete exe;
			}
			else
			{
				std::string a = tool::string::WStringToString(CmdCommand);
				std::cout << "\'" << a << "\' 不是内部或外部命令，也不是可运行的程序\n或批处理文件。";
			}
		}
	}
	base_executable * vssd_optcmd::GetTaskByName(const std::wstring& Name)
	{
		 
		if (v_match(Name, L"dir"))
		{
			return new vssdDir();
		}
		else if (v_match(Name, L"del"))
		{
			return new vssdDel();
		}
		else if (v_match(Name, L"save"))
		{
			return new vssdSave();
		} 
		else if (v_match(Name, L"load"))
		{
			return new vssdLoad();
		} 
		else if (v_match(Name, L"mklink"))
		{
			return new vssdMklink();
		}
		//cd命令解析
		else if (v_match(Name, L"cd"))
		{
			return new vssdCd();
		}
		//rd命令解析
		else if (v_match(Name, L"rd"))
		{
			return new vssdRd();
		}
		//ren命令解析
		else if (v_match(Name, L"ren"))
		{
			return new vssdRen();   
		}
		//copy命令解析
		else if (v_match(Name, L"copy"))
		{
			return new vssdCopy(); 
		}
		//move命令解析
		else if (v_match(Name, L"move"))
		{ 
			return new vssdMove(); 
		} 
		//清屏命令解析
		else if (v_match(Name, L"cls"))
		{
			return new vssdCls();
		}
		//创建文件夹命令解析
		else if (v_match(Name, L"md"))
		{
			return new vssdMkdir();
		}
		//查看文件内容命令解析
		else if (v_match(Name, L"cat"))
		{ 
			return new vssdCat();
		}
		else
		{
			return nullptr;
		}

	}

}
