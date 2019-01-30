#include "pch.h" 

//�����ļ�����dir


sjh::vssd_Inode * sjh::vssd_vcmd::v_FindPathForFirst(vssd_disk & MyVssd, std::wstring  PathCommand, tool_path &aPath)
{
	tools_vssd::Trim(PathCommand); 
	tool_path Nowpath = MyVssd.GetNooowPan()->GetNowPath();
	std::wstring pathstring = PathCommand;
	

	tool_path path;
	path.SetInodesByWstring(pathstring); 
	sjh::vssd_Inode * longNowf = Nowpath.GetNow();

	int flag_tofirstif = 1;
	for (size_t i = 0; i < path.Inodes.size(); i++)
	{
		//˵���Ǵ��̿�ͷ����Ϊ����·��
		if (flag_tofirstif && path.Inodes[i].length() == 2 && path.Inodes[i].at(1) == ':')
		{
			Nowpath.Clear(); 
			int Result = MyVssd.GetGenius()->FindSelfSubForFirst(path.Inodes[i], 0);
			if (Result != sjh::vssd_Inode::NOT_FINDED) {
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
			if (Result != sjh::vssd_Inode::NOT_FINDED) {
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

void sjh::vssd_vcmd::v_jump(vssd_disk & MyVssd, std::wstring & JumpTo)
{
	sjh::vssd_pan* Top = MyVssd.FindPanFromName(JumpTo);
	if(Top) MyVssd.SetNooowPan(Top);
}

bool sjh::vssd_vcmd::v_match(std::wstring & CmdCommand, std::wstring  MatchString)
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
	//�������������������
	if (CmdCommand.length() == 0)
	{
	}
	//dir�������
	else if (v_match(CmdCommand, L"dir"))
	{  
		sjh::vssdDir::vDir(MyVssd, rear); 
	}
	//del�������
	else if (v_match(CmdCommand, L"del"))
	{  
		sjh::vssdDel::vDel(MyVssd, rear);  
	}
	//save�������
	else if (v_match(CmdCommand, L"save"))
	{   
		sjh::vssdSave::vSave(MyVssd, rear); 
	}
	//load�������
	else if (v_match(CmdCommand, L"load"))
	{   
		sjh::vssdLoad::vLoad(MyVssd, rear); 
	}
	//mkLink�������
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
	//cd�������
	else if (v_match(CmdCommand, L"cd"))
	{   
		sjh::vssd_pan *Pan = MyVssd.GetNooowPan(); 
		if (v_match(rear, L"/") || v_match(rear, L"\\"))
		{
			while (Pan->GetNowPath().Inodes.size() > 2) Pan->GetNowPath().DeleteOneSub();
		}
		else
		{
			sjh::vssdCd::vCd(MyVssd, rear);
		}
	}
	//rd�������
	else if (v_match(CmdCommand, L"rd"))
	{  
		sjh::vssdRd::vRd(MyVssd, rear); 
	}
	//ren�������
	else if (v_match(CmdCommand, L"ren"))
	{ 
		//ʵ�ַָ����������������������
		int spacePos = rear.find(L" ", 1);
		if (spacePos != rear.npos)
		{ 
			std::wstring rearSrc = rear.substr(0, spacePos-0);
			std::wstring reardisName = rear.substr(spacePos + 1, rear.size() - spacePos-1); 
			sjh::vssdRen::vRen(MyVssd, rearSrc, reardisName); 
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
			tools_vssd::Trim(rearSrc);
			tools_vssd::Trim(rearDes);
			sjh::vssdCopy::vCopy(MyVssd, rearSrc, rearDes);
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
			tools_vssd::Trim(rearSrc);
			tools_vssd::Trim(rearDes);
			sjh::vssdMove::vMove(MyVssd, rearSrc, rearDes);
		}
		else
		{ 
			sjh::vssdMove::vMove(MyVssd, rear);
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
		sjh::vssdCls::vCls();
	}
	//�����ļ����������
	else if (v_match(CmdCommand, L"md"))
	{  
		sjh::vssdMd::vMd(MyVssd, rear);
	}
	//�鿴�ļ������������
	else if (v_match(CmdCommand, L"cat"))
	{  
		sjh::vssdCat::vCat(MyVssd, rear); 
	}
	else { 
	std::string a =  sjh::tools_vssd::WStringToString(cmd);
	std::cout << "\'" << a << "\' �����ڲ����ⲿ���Ҳ���ǿ����еĳ���\n���������ļ���";
		 
	}

}

