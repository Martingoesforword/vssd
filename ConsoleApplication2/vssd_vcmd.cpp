#include "pch.h" 

//�����ļ�����dir


sjh::vssd_folder * sjh::vssd_vcmd::v_FindPathForFirst(vssd_disk & MyVssd, std::wstring & PathCommand, tool_path &aPath)
{
	sjh::vssd_pan *MyTop = MyVssd.GetNowTop();
	static tool_path Nowpath;
	Nowpath = MyTop->NowPath;//Ŀǰλ��
	//Nowpath
	std::wstring pathstring = PathCommand;
	tools_vssd::Trim(&pathstring);
	tool_path path;
	path.PathToFolders(pathstring);
	//path��pathstring
	sjh::vssd_folder * longNowf = Nowpath.GetNow();

	int flag_tofirstif = 1;
	for (size_t i = 0; i < path.Folders.size(); i++)
	{
		//˵���Ǵ��̿�ͷ����Ϊ����·��
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
			while (longNowf->VssdTypeCode == 2) longNowf = longNowf->SubFolders[0];
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
				Nowpath.DeletOne();
			}

		}
		else if (path.Folders.at(i) == L".")
		{

		}
		//·���з�'n:' '..' '.'
		else
		{

			longNowf = longNowf->FindForFirst(path.Folders[i]);
			if (!longNowf)
			{

				return nullptr;
			}
			Nowpath.AddOne(longNowf);
			if (longNowf->VssdTypeCode == 2 && i + 1 == path.Folders.size())
			{
				aPath = Nowpath; return longNowf;
			}




			while (longNowf->VssdTypeCode == 2) longNowf = longNowf->SubFolders[0];
		}

	}

	aPath = Nowpath;
	if (longNowf) longNowf->SetCheck();
	return longNowf;


}

void sjh::vssd_vcmd::v_jump(vssd_disk & MyVssd, std::wstring & JumpTo)
{
	sjh::vssd_pan* Top = MyVssd.FindTop(JumpTo);
	MyVssd.SetNowTop(Top);
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
std::wstring sjh::vssd_vcmd::v_getrear(std::wstring & CmdCommand, std::wstring  Command)
{
	return CmdCommand.substr(Command.size(), CmdCommand.size() - 3);
}
void sjh::vssd_vcmd::v_cmd_comein(vssd_disk & MyVssd, std::wstring & CmdCommand)
{
	sjh::vssd_pan *MyTop = MyVssd.GetNowTop();
	tools_vssd::Trim(CmdCommand);
	std::wstring rear;
	//�������������������
	if (CmdCommand.length() == 0)
	{
	}
	//dir�������
	else if (v_match(CmdCommand, L"dir"))
	{
		if (CmdCommand.length() == 3)
		{
			sjh::vssdDir::vDir(MyTop);
		}
		else
		{
			rear = v_getrear(CmdCommand, L"dir");
			tools_vssd::Trim(rear);
			sjh::vssdDir::vDir(MyVssd, rear);
		}

	}
	//del�������
	else if (v_match(CmdCommand, L"del"))
	{

		rear = v_getrear(CmdCommand, L"del");
		tools_vssd::Trim(rear);
		sjh::vssdDel::vDel(MyVssd, rear);


	}
	//save�������
	else if (v_match(CmdCommand, L"save"))
	{


		rear = v_getrear(CmdCommand, L"save");
		tools_vssd::Trim(rear);

		sjh::vssdSave::vSave(MyVssd, rear);

	}
	//load�������
	else if (v_match(CmdCommand, L"load"))
	{


		rear = v_getrear(CmdCommand, L"load");
		tools_vssd::Trim(rear);

		sjh::vssdLoad::vLoad(MyVssd, rear);

	}
	//mkLink�������
	else if (v_match(CmdCommand, L"mklink"))
	{

		rear = v_getrear(CmdCommand, L"mklink");
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
		if (CmdCommand.length() == 2)
		{
			sjh::vssdCd::vCd(MyTop);
		}
		else
		{

			rear = v_getrear(CmdCommand, L"cd");
			tools_vssd::Trim(rear);
			sjh::vssdCd::vCd(MyVssd, rear);
		}

	}
	//rd�������
	else if (v_match(CmdCommand, L"rd"))
	{
		if (CmdCommand.length() == 2)
		{
			sjh::vssdRd::vRd(MyVssd);
		}
		else
		{
			rear = v_getrear(CmdCommand, L"rd");
			tools_vssd::Trim(rear);
			sjh::vssdRd::vRd(MyVssd, rear);
		}

	}
	//ren�������
	else if (v_match(CmdCommand, L"ren"))
	{



		rear = v_getrear(CmdCommand, L"ren");
		int spacePos = rear.find(L" ", 1);
		if (spacePos != -1)
		{

			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring reardisName = rear.substr(spacePos + 1, rear.length() - spacePos);

			sjh::vssdRen::vRen(MyVssd, rearSrc, reardisName);

		}
		else
		{
			std::wstring rearSrc = rear;
			tools_vssd::Trim(rear);
			sjh::vssdRen::vRen(MyVssd, rear);
		}


		//����
		//0123456789
		//023203 323

	}
	//copy�������
	else if (v_match(CmdCommand, L"copy"))
	{


		rear = v_getrear(CmdCommand, L"copy");
		tools_vssd::Trim(rear);
		int spacePos = rear.find(L" ", 0);
		if (spacePos != -1)
		{

			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring rearDes = rear.substr(spacePos + 1, rear.length() - spacePos);
			tools_vssd::Trim(rearSrc);
			tools_vssd::Trim(rearDes);
			if (rearSrc.at(0) == L'@')
			{
				sjh::tool_path a;
				sjh::vssd_folder *folder = v_FindPathForFirst(MyVssd, rearDes, a);
				if (!folder)
				{
					a.PathToFolders(rearDes);
					if (a.Folders[0].size() > 1 && a.Folders[0].at(1) != L':')
					{
						MyVssd.GetNowTop()->GetNowPos()->Build(MyVssd, a);
					}
					else
					{
						MyVssd.GetGenius()->Build(MyVssd, a);
					}

				}
				folder = v_FindPathForFirst(MyVssd, rearDes, a);
				folder->VssdTypeCode = 0;

				std::wstring RealSrc = rearSrc.substr(1, rearSrc.length() - 1);




				char ch;

				std::ifstream RealFile(RealSrc, std::ios::binary);

				if (!RealFile.is_open())
				{
					std::cout << "Error opening file"; exit(1);
				}

				while (!RealFile.eof())
				{
					ch = ' ';
					RealFile.read(&ch, 1);
					folder->Content.push_back(ch);




				}
				RealFile.close();
				//��������vector<std::wstring>
				//�õ��ļ���
				//�ж��ļ�����

				//����Ŀ�������ļ�rearSrc1
				//����sjh::vssdCopy::vCopy(MyVssd, rearSrc1, reardis);

			}
			else if (rearDes.at(0) == L'@')
			{
				sjh::tool_path a;
				sjh::vssd_folder *folder = v_FindPathForFirst(MyVssd, rearSrc, a);

				std::wstring RealDes = rearDes.substr(1, rearDes.length() - 1);
				std::ofstream DesFile(RealDes, std::ios::binary);
				if (DesFile.is_open())
				{
					std::wstring data;
					tools_vssd::GetStringAnd0(folder->Content, 0, folder->Content.size(), data);

					DesFile.write((const char*)&data[0], data.size() * 2);
					DesFile.close();
				}
				else
				{
					std::cout << "Error opening file" << std::endl;
				}

				//�õ��ļ���
				//�����ļ�ָ�룬
				//��content���Բ�д���ļ��� 
			}
			else
			{
				sjh::vssdCopy::vCopy(MyVssd, rearSrc, rearDes);
			}



		}



	}
	//move�������
	else if (v_match(CmdCommand, L"move"))
	{


		rear = v_getrear(CmdCommand, L"move");
		tools_vssd::Trim(rear);
		int spacePos = rear.find(L" ", 0);
		if (spacePos != -1)
		{

			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring reardis = rear.substr(spacePos + 1, rear.length() - spacePos);

			sjh::vssdMove::vMove(MyVssd, rearSrc, reardis);

		}
		else
		{
			std::wstring reardis = rear;
			tools_vssd::Trim(rear);
			sjh::vssdMove::vMove(MyVssd, reardis);
		}


		//����
		//0123456789
		//023203 323

	}
	//��ת���������
	else if (CmdCommand.length() == 2 && CmdCommand.at(1) == ':')
	{
		rear = CmdCommand;
		v_jump(MyVssd, rear);
	}
	//�����������
	else if (v_match(CmdCommand, L"cls"))
	{
		sjh::vssdCls::vCls();
	}
	//�����ļ����������
	else if (v_match(CmdCommand, L"mkdir"))
	{

		rear = v_getrear(CmdCommand, L"mkdir");
		tools_vssd::Trim(rear);
		sjh::vssdMd::vMd(MyVssd, rear);

	}
	//�鿴�ļ������������
	else if (v_match(CmdCommand, L"cat"))
	{

		rear = v_getrear(CmdCommand, L"cat");
		tools_vssd::Trim(rear);
		sjh::vssdCat::vCat(MyVssd, rear);

	}

}

