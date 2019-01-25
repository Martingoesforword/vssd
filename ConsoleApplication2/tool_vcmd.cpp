#include "pch.h" 

//当下文件夹下dir


sjh::vssd_folder * sjh::tool_vcmd::v_FindPathForFirst(vssd_disk & MyVssd, std::wstring & PathCommand, tool_path &aPath)
{
	sjh::vssd_pan *MyTop = MyVssd.GetNowTop();
	static tool_path Nowpath;
	Nowpath = MyTop->NowPath;//目前位置
	//Nowpath
	std::wstring pathstring = PathCommand;
	vssd_tool::Trim(&pathstring); 
	tool_path path;
	path.PathToFolders(pathstring);
	//path，pathstring
	sjh::vssd_folder * longNowf = Nowpath.GetNow();	

	int flag_tofirstif = 1;
	for (size_t i = 0; i < path.Folders.size(); i++)
	{
		//说明是磁盘开头，则为绝对路径
		if (flag_tofirstif && path.Folders[i].length() == 2 && path.Folders[i].at(1) == ':') {
			Nowpath.Folders.clear(); 
			Nowpath.RealFolders.clear();
			Nowpath.Folders.push_back(L"");
			Nowpath.SetRealpath(MyVssd.GetGenius(),0) ; 
			 
			longNowf = Nowpath.GetNow()->FindForFirst(path.Folders[i]);
			
			
			if (!longNowf) {
				return nullptr;
			}
			Nowpath.AddOne(longNowf);
			while(longNowf->VssdTypeCode == 2) longNowf = longNowf->SubFolders[0];
			flag_tofirstif = 0;
		}
		else if (path.Folders.at(i)== L"..") {
			if (Nowpath.RealFolders.size() < 3) {
				return nullptr;
			}
			else {
				Nowpath.DeletOne();
			}

		}
		else if (path.Folders.at(i)== L".") {

		}
		//路径中非'n:' '..' '.'
		else {
			
			longNowf = longNowf->FindForFirst(path.Folders[i]);
			if (!longNowf) {

				return nullptr;
			}
			Nowpath.AddOne(longNowf);
			if (longNowf->VssdTypeCode == 2 && i + 1 == path.Folders.size()) { aPath = Nowpath; return longNowf; }
			 

			
			 
			while(longNowf->VssdTypeCode == 2) longNowf = longNowf->SubFolders[0];
		}

	}
	 
	aPath = Nowpath;
	if (longNowf) longNowf->SetCheck();
	return longNowf;
	 
	 
}

void sjh::tool_vcmd::v_jump(vssd_disk & MyVssd, std::wstring & JumpTo)
{
	sjh::vssd_pan* Top = MyVssd.FindTop(JumpTo);
	MyVssd.SetNowTop(Top);
}

void sjh::tool_vcmd::v_cmd_comein(vssd_disk & MyVssd, std::wstring & CmdCommand)
{
	sjh::vssd_pan *MyTop = MyVssd.GetNowTop();
	vssd_tool::Trim(CmdCommand);
	std::wstring rear;

	//分析命令名与命令参数
	if (CmdCommand.length() == 0) {
			
	}
	//dir命令解析
	else if (CmdCommand.length() >= 3 && CmdCommand.substr(0,3).compare(L"dir") == 0) {			
		if (CmdCommand.length() == 3) {
			vDir(MyTop);
		}
		else {
			rear = CmdCommand.substr(3, CmdCommand.length() - 3);
			vssd_tool::Trim(rear);
			vDir(MyVssd,rear);
		}
		
	}
	//del命令解析
	else if (CmdCommand.length() >= 3 && CmdCommand.substr(0, 3).compare(L"del") == 0) {
		 
		rear = CmdCommand.substr(3, CmdCommand.length() - 3);
		vssd_tool::Trim(rear);
		vDel(MyVssd, rear);
		 

	}
	//save命令解析
	else if (CmdCommand.length() > 4 && CmdCommand.substr(0, 4).compare(L"save") == 0) {


		rear = CmdCommand.substr(4, CmdCommand.length() - 4);
		vssd_tool::Trim(rear);
		 
		vSave(MyVssd, rear);

	}
	//load命令解析
	else if (CmdCommand.length() > 4 && CmdCommand.substr(0, 4).compare(L"load") == 0) {


		rear = CmdCommand.substr(4, CmdCommand.length() - 4);
		vssd_tool::Trim(rear);

		vLoad(MyVssd, rear);

	}
	//mkLink命令解析
	else if (CmdCommand.length() > 6 && CmdCommand.substr(0, 6).compare(L"mklink") == 0) {

		rear = CmdCommand.substr(6, CmdCommand.length() - 6);
		int spacePos = rear.find(L" ", 1);
		if (spacePos != -1) {

			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring reardisName = rear.substr(spacePos + 1, rear.length() - spacePos);

			vMklink(MyVssd, rearSrc, reardisName);

		}
		 

		 

	}
	//cd命令解析
	else if (CmdCommand.length() >= 2 && CmdCommand.substr(0, 2).compare(L"cd") == 0) {
		if (CmdCommand.length() == 2) {
			vCd(MyTop);
		}
		else {

			rear = CmdCommand.substr(2, CmdCommand.length() - 2);
			vssd_tool::Trim(rear);
			vCd(MyVssd, rear);
		}

	} 
	//rd命令解析
	else if (CmdCommand.length() >= 2 && CmdCommand.substr(0, 2).compare(L"rd") == 0) {
		if (CmdCommand.length() == 2) {
			vRd(MyVssd);
		}
		else {
			rear = CmdCommand.substr(2, CmdCommand.length() - 2);
			vssd_tool::Trim(rear);
			vRd(MyVssd, rear);
		}

	}
	//ren命令解析
	else if (CmdCommand.length() > 3 && CmdCommand.substr(0, 3).compare(L"ren") == 0) {
		
		 

		rear = CmdCommand.substr(3, CmdCommand.length() - 3);
		int spacePos = rear.find(L" ", 1);
		if (spacePos != -1) {

			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring reardisName = rear.substr(spacePos + 1, rear.length() - spacePos);
			  
			vRen(MyVssd, rearSrc, reardisName);

		}
		else {
			std::wstring rearSrc = rear;
			vssd_tool::Trim(rear);
			vRen(MyVssd, rear);
		}
		
		 
		//解释
		//0123456789
		//023203 323

	}
	//copy命令解析
	else if (CmdCommand.length() > 4 && CmdCommand.substr(0, 4).compare(L"copy") == 0) {


		rear = CmdCommand.substr(4, CmdCommand.length() - 4);
		vssd_tool::Trim(rear);
		int spacePos = rear.find(L" ", 0);
		if (spacePos != -1) {

			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring rearDes = rear.substr(spacePos + 1, rear.length() - spacePos);
			vssd_tool::Trim(rearSrc);
			vssd_tool::Trim(rearDes);
			if (rearSrc.at(0) == L'@') {
				sjh::tool_path a;
				sjh::vssd_folder *folder = v_FindPathForFirst(MyVssd, rearDes, a);
				if (!folder) {
					a.PathToFolders(rearDes);
					if (a.Folders[0].size() > 1 && a.Folders[0].at(1) != L':') {
						MyVssd.GetNowTop()->GetNowPos()->Build(MyVssd, a);
					}
					else {
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
				//读并放入vector<std::wstring>
				//得到文件名
				//判断文件类型

				//建立目的虚拟文件rearSrc1
				//调用vCopy(MyVssd, rearSrc1, reardis);

			}else if (rearDes.at(0) == L'@') {
				sjh::tool_path a;
				sjh::vssd_folder *folder = v_FindPathForFirst(MyVssd, rearSrc, a);

				std::wstring RealDes = rearDes.substr(1, rearDes.length() - 1);
				std::ofstream DesFile(RealDes, std::ios::binary);
				if (DesFile.is_open())
				{
					std::wstring data;
					vssd_tool::GetStringAnd0(folder->Content, 0, folder->Content.size(), data);

					DesFile.write((const char*)&data[0], data.size()*2); 
					DesFile.close(); 
				}
				else {
					std::cout << "Error opening file" << std::endl;
				}
				 
				//得到文件名
				//建立文件指针，
				//读content属性并写入文件中 
			}
			else {
				vCopy(MyVssd, rearSrc, rearDes);
			}

			

		}
		 
		 

	}
	//move命令解析
	else if (CmdCommand.length() > 4 && CmdCommand.substr(0, 4).compare(L"move") == 0) {

		 
		rear = CmdCommand.substr(4, CmdCommand.length() - 4);
		vssd_tool::Trim(rear);
		int spacePos = rear.find(L" ", 0);
		if (spacePos != -1) {

			std::wstring rearSrc = rear.substr(0, spacePos);
			std::wstring reardis = rear.substr(spacePos + 1, rear.length() - spacePos);
			 
			vMove(MyVssd, rearSrc, reardis);

		}
		else {
			std::wstring reardis = rear;
			vssd_tool::Trim(rear);
			vMove(MyVssd, reardis);
		}


		//解释
		//0123456789
		//023203 323

	}
	//跳转盘命令解析
	else if (CmdCommand.length() == 2 && CmdCommand.at(1) == ':') {
		rear = CmdCommand;
		v_jump(MyVssd, rear);
	}
	//清屏命令解析
	else if (CmdCommand.length() == 3 && CmdCommand.compare(L"cls") == 0) {
		vCls();
	}
	//创建文件夹命令解析
	else if (CmdCommand.length() > 5 && CmdCommand.substr(0, 5).compare(L"mkdir") == 0) {
		 
		rear = CmdCommand.substr(5, CmdCommand.length() - 5);
		vssd_tool::Trim(rear);
		vMd(MyVssd, rear);

	}
	//查看文件内容命令解析
	else if (CmdCommand.length() > 3 && CmdCommand.substr(0, 3).compare(L"cat") == 0) {

	rear = CmdCommand.substr(3, CmdCommand.length() - 3);
	vssd_tool::Trim(rear);
	vCat(MyVssd, rear);

	}
	  
}

 