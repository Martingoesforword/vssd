#include "pch.h"  
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
		vssd_inode * longNowf = Nowpath.GetNowPtr();

		int flag_tofirstif = 1;
		for (size_t i = 0; i < path.Inodes.size(); i++)
		{
			//˵���Ǵ��̿�ͷ����Ϊ����·��
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
			//·���з�'n:' '..' '.'
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
		return CmdCommand.compare(MatchString) == 0;
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
				//������ֵ
			} 
		}
		return RET_WELL_OPERATION;
	}

	 

	void vssd_optcmd::TypeCode_UI_Explainer(VirtualDisk & MyVssd, std::wstring  CmdCommand)
	{
		 
		std::vector<std::wstring> Rears;
		tool::stringtools::Split(CmdCommand, Rears, L" ");
		//�������������������
		if (CmdCommand.length() == 0) { } 
		else if (CmdCommand.length() == 2 && CmdCommand.at(1) == ':')
		{
			v_jump(MyVssd, CmdCommand);
			return;
		} 
		if (Rears.size())
		{
			base_executable *exe = GetTaskByName(Rears[0]);
			if (exe != nullptr)
			{
				exe->Execute(MyVssd, Rears);
				exe->GetStatus();
				delete exe;
			}
			else
			{
				std::string a = tool::stringtools::WStringToString(CmdCommand);
				std::cout << "\'" << a << "\' �����ڲ����ⲿ���Ҳ���ǿ����еĳ���\n���������ļ���";
			}
		}
	}
	base_executable * vssd_optcmd::GetTaskByName(std::wstring Name)
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
		//cd�������
		else if (v_match(Name, L"cd"))
		{
			return new vssdCd();
		}
		//rd�������
		else if (v_match(Name, L"rd"))
		{
			return new vssdRd();
		}
		//ren�������
		else if (v_match(Name, L"ren"))
		{
			return new vssdRen();   
		}
		//copy�������
		else if (v_match(Name, L"copy"))
		{
			return new vssdCopy(); 
		}
		//move�������
		else if (v_match(Name, L"move"))
		{ 
			return new vssdMove(); 
		} 
		//�����������
		else if (v_match(Name, L"cls"))
		{
			return new vssdCls();
		}
		//�����ļ����������
		else if (v_match(Name, L"md"))
		{
			return new vssdMkdir();
		}
		//�鿴�ļ������������
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
