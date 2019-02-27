#include "pch.h"  
#include "vssd_optcmd.h"
const std::wstring sjh::vssd_optcmd::GUIDE_SYMBOL = L">";
namespace sjh {  
	vssd_inode * vssd_optcmd::v_FindPathForFirst(const VirtualDisk & MyVssd,const std::wstring&  PathCommand)
	{
		tools_path a;
		return v_FindPathForFirst(MyVssd, PathCommand, a);
	}

	vssd_inode * vssd_optcmd::v_FindPathForFirst(const VirtualDisk & MyVssd, const std::wstring&  PathCommand, tools_path &aPath)
	{
		tools_path	 Path(PathCommand); 
		tools_path	 NowPath(MyVssd.GetNooowPan()->GetNowPath());
		//Nowpath  copy and swap策略  

		const vssd_inode * longNowf(NowPath.GetNowPtr());

		int flag_tofirstif(1);
		for (size_t i = 0; i < Path.Inodes.size(); i++)
		{
			//说明是磁盘开头，则为绝对路径
			if (flag_tofirstif && Path.Inodes[i].size() == 2 && Path.Inodes[i].at(1) == ':')
			{
				NowPath.Clear();
				size_t Result = MyVssd.GetGenius()->FindSelfSubForNext(Path.Inodes[i], 0);
				if (vssd_inode::IsFinded(Result) ) {
					longNowf = MyVssd.GetGenius()->GetSubInodes()[Result];
				}
				else {
					return nullptr;
				}
				NowPath.LoadOneSub(longNowf); 
			}
			else if (Path.Inodes.at(i) == L"..")
			{
				if (NowPath.RealInodes.size() < 2)
				{
					return nullptr;
				}
				else
				{
					NowPath.DeleteOneSub();
				}

			}
			else if (Path.Inodes.at(i) == L".") { } 
			else 
			{
				size_t Result = longNowf->FindSelfSubForNext(Path.Inodes[i], 0);
				if (vssd_inode::IsFinded(Result))
				{
					longNowf = longNowf->GetSubInodes()[Result];
					NowPath.LoadOneSub(longNowf);
					if (longNowf->IsLinkD())
					{
						if ((i + 1) == Path.Inodes.size())
						{
							aPath = NowPath;
							return (vssd_inode *)longNowf;
						} 
						else{
							 longNowf = CheckLink(MyVssd, (vssd_inode*)longNowf);
						}
					} 
				}
				else { return nullptr; } 
				
			}
			flag_tofirstif = 0;
		}
		aPath = NowPath; 
		return const_cast< vssd_inode *>(longNowf);
	}

	void vssd_optcmd::v_FindPathForAll(const VirtualDisk & MyVssd, std::wstring PathCommand, std::vector<vssd_inode*>& sets)  
	{
		tools_path	 Path(PathCommand);
		tools_path	 NowPath(MyVssd.GetNooowPan()->GetNowPath());
		//Nowpath  copy and swap策略  

		const vssd_inode * longNowf(NowPath.GetNowPtr());

		int flag_tofirstif(1);
		for (size_t i = 0; i < Path.Inodes.size()-1; i++)
		{
			//说明是磁盘开头，则为绝对路径
			if (flag_tofirstif && Path.Inodes[i].size() == 2 && Path.Inodes[i].at(1) == ':')
			{
				NowPath.Clear();
				size_t Result = MyVssd.GetGenius()->FindSelfSubForNext(Path.Inodes[i], 0);
				if (vssd_inode::IsFinded(Result)) {
					longNowf = MyVssd.GetGenius()->GetSubInodes()[Result];
				}
				else {
					return;
				}
				NowPath.LoadOneSub(longNowf);
			}
			else if (Path.Inodes.at(i) == L"..")
			{
				if (NowPath.RealInodes.size() < 2)
				{
					return;
				}
				else
				{
					NowPath.DeleteOneSub();
				}

			}
			else if (Path.Inodes.at(i) == L".") {}
			else
			{
				size_t Result = longNowf->FindSelfSubForNext(Path.Inodes[i], 0);
				if (vssd_inode::IsFinded(Result))
				{
					longNowf = longNowf->GetSubInodes()[Result];
					NowPath.LoadOneSub(longNowf);
					if (longNowf->IsLinkD())
					{
						if ((i + 1) == Path.Inodes.size())
						{  
							break;
						}
						else {
							longNowf = CheckLink(MyVssd, (vssd_inode*)longNowf);
						}
					}
				}
				else { return; }

			}
			flag_tofirstif = 0;
		}
		longNowf = NowPath.GetNowPtr();
		longNowf->FindSelfSubForAll(Path.Inodes[Path.Inodes.size() - 1], sets); 
		return;
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
		return CmdCommand == MatchString;
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
		using namespace tool::string;

		if (CmdCommand.size() == 0) {} 
		std::vector<std::wstring>	Rears; 
		Split(CmdCommand, Rears, L" ");
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
				std::string a = WStringToString(CmdCommand);
				std::cout << "\'" << a << "\' 不是内部或外部命令，也不是可运行的程序\n或批处理文件。";
			}
		}
	}
	vssd_inode * vssd_optcmd::CheckLink(const VirtualDisk& a,  vssd_inode *aInode)
	{
		vssd_inode *Inode = aInode;
		while (Inode && Inode->IsLinkD())
		{
			Inode = v_FindPathForFirst(a, Inode->GetLinkPath()->GetPathWstring());
		}  
		return Inode;
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
