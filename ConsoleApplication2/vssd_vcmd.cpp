#include "vssd_vcmd.h"

namespace sjh {  
	
	vssd_inode * vssd_vcmd::v_FindPathForFirst(vssd_disk & MyVssd, std::wstring  PathCommand, tools_path &aPath)
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
			//˵���Ǵ��̿�ͷ����Ϊ����·��
			if (flag_tofirstif && path.Inodes[i].length() == 2 && path.Inodes[i].at(1) == ':')
			{
				Nowpath.Clear();
				int Result = MyVssd.GetGenius()->FindSelfSubForFirst(path.Inodes[i], 0);
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
				int Result = longNowf->FindSelfSubForFirst(path.Inodes[i], 0);
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

	void vssd_vcmd::v_jump(vssd_disk & MyVssd, std::wstring & JumpTo)
	{
		vssd_pan* Top = MyVssd.FindPanFromName(JumpTo);
		if (Top) MyVssd.SetNooowPan(Top);
	}

	bool vssd_vcmd::v_match(std::wstring & CmdCommand, std::wstring  MatchString)
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

	void vssd_vcmd::TypeCode_UI_Guider(vssd_disk & manager,int GuiderCode)
	{
		std::wcout << manager.GetNooowPan()->GetNowPathWString() << GUIDESYMBOL;
	}
	std::wstring vssd_vcmd::TypeCode_UI_GetCommandString()
	{
		std::string Command;
		while (Command.size() == 0)
		{
			std::getline(std::cin, Command);
		}
		return tool::stringtools::StringToWString(Command);
	}
	void vssd_vcmd::TypeCode_UI(vssd_disk & manager)
	{
		while (1)
		{ 
			TypeCode_UI_Guider(manager, 0);  
			std::wstring Command = TypeCode_UI_GetCommandString();
			if (sjh::tool::stringtools::WStringMatch(Command, L"exit")) 
			{
				break;
			}
			else
			{
				TypeCode_UI_Explainr(manager, Command);
				std::cout << "\n";
			} 
		}
	}

	 

	void vssd_vcmd::TypeCode_UI_Explainr(vssd_disk & MyVssd, std::wstring  CmdCommand)
	{

		tool::stringtools::Trim(CmdCommand);
		std::wstring rear;
		std::wstring cmd;
		int spacePos = CmdCommand.find(L" ", 1);
		if (spacePos != CmdCommand.npos) {
			rear = CmdCommand.substr(spacePos + 1, CmdCommand.size() - spacePos - 1);
			cmd = CmdCommand.substr(0, CmdCommand.size() - 0);
		}
		else {
			cmd = CmdCommand;
		}
		//�������������������
		if (CmdCommand.length() == 0)
		{
		}
		//dir�������
		else if (v_match(CmdCommand, L"dir"))
		{
			vssdDir vDir_task1 ;
		}
		//del�������
		else if (v_match(CmdCommand, L"del"))
		{
			vssdDel vDel ;
		}
		//save�������
		else if (v_match(CmdCommand, L"save"))
		{
			vssdSave vSave ;
		}
		//load�������
		else if (v_match(CmdCommand, L"load"))
		{
			vssdLoad vLoad ;
		}
		//mkLink�������
		else if (v_match(CmdCommand, L"mklink"))
		{
			int spacePos = rear.find(L" ", 1);
			if (spacePos != -1)
			{
				std::wstring rearSrc = rear.substr(0, spacePos);
				std::wstring reardisName = rear.substr(spacePos + 1, rear.length() - spacePos);
				vssdMklink vMklink ;
			}

		}
		//cd�������
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
		//rd�������
		else if (v_match(CmdCommand, L"rd"))
		{
			vssdRd vRd ;
		}
		//ren�������
		else if (v_match(CmdCommand, L"ren"))
		{
			//ʵ�ַָ����������������������
			int spacePos = rear.find(L" ", 1);
			if (spacePos != rear.npos)
			{
				std::wstring rearSrc = rear.substr(0, spacePos - 0);
				std::wstring reardisName = rear.substr(spacePos + 1, rear.size() - spacePos - 1);
				vssdRen vRen ;
			}

			//����:�����������-��ʼ��������/���������� = �������� 
			//  (-10,60-10)        (-10, (60+10)/10 )
			//-10 0 10 20 30 40 50 60 70 80 90 
			//  9 3  2  3  2  0  3  _  3  2  3

		}
		//copy�������
		else if (v_match(CmdCommand, L"copy"))
		{
			int spacePos = rear.find(L" ", 0);
			if (spacePos != -1)
			{
				std::wstring rearSrc = rear.substr(0, spacePos);
				std::wstring rearDes = rear.substr(spacePos + 1, rear.length() - spacePos - 1);
				tool::stringtools::Trim(rearSrc);
				tool::stringtools::Trim(rearDes);
				vssdCopy vCopy ;
			}
		}
		//move�������
		else if (v_match(CmdCommand, L"move"))
		{

			int spacePos = rear.find(L" ", 0);
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
		//��ת���������
		else if (CmdCommand.length() == 2 && CmdCommand.at(1) == ':')
		{
			v_jump(MyVssd, CmdCommand);
		}
		//�����������
		else if (v_match(CmdCommand, L"cls"))
		{
			vssdCls vCls ;
		}
		//�����ļ����������
		else if (v_match(CmdCommand, L"md"))
		{
			vssdMkdir vMd ;
		}
		//�鿴�ļ������������
		else if (v_match(CmdCommand, L"cat"))
		{

			vssdCat vCat ;
		}
		else {
			std::string a = tool::stringtools::WStringToString(cmd);
			std::cout << "\'" << a << "\' �����ڲ����ⲿ���Ҳ���ǿ����еĳ���\n���������ļ���";

		}

	}

}