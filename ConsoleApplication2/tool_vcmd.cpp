#include "pch.h" 

//当下文件夹下dir
void sjh::tool_vcmd::vDir(sjh::vssd_foldertop * Top)
{
	sjh::vssd_folder *now = Top->GetNowPos();
	
	while (now->VssdTypeCode == 2) { 
		if(now) now = now->SubFolders[0]; 
		else {
			return;
		}
	}
	now->ShowOffSub(1,Top->NowPath.FoldersToPath());
	 
}
//当下文件夹下cd
void sjh::tool_vcmd::vCd(sjh::vssd_foldertop * MyTop) 
{

	MyTop->ShowNowPos();
}
//当下文件夹下rd
void sjh::tool_vcmd::vRd(vssd & MyVssd) {
	if (MyVssd.GetNowTop()->NowPath.RealFolders.size() >= 3) {
		MyVssd.GetNowTop()->GetNowPos()->DeleteLinks();
		MyVssd.GetNowTop()->NowPath.RealFolders.at(MyVssd.GetNowTop()->NowPath.RealFolders.size() - 2)->DeletOne(MyVssd.GetNowTop()->GetNowPos());

		MyVssd.GetNowTop()->NowPath.DeletOne(); 
		std::cout << "VSSD ERROR : NowPos folder is deleted just！" << std::endl;
	}
	else {
		std::cout << "VSSD ERROR : Root folder cannot be deleted！" << std::endl;
	}
	

}

void sjh::tool_vcmd::vRd(vssd & MyVssd, std::wstring & RdCommand)
{
	 
	tool_path a;
	sjh::vssd_folder * folder = v_FindPath(MyVssd, RdCommand, a);
	if (!folder) { std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return; }
	folder->DeleteLinks();
	if (folder->isFile()) {
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vDel(MyVssd, RdCommand);
		return;
	}
	if (folder && a.Folders.size() >= 3) {
		a.RealFolders.at(a.RealFolders.size() - 2)->DeletOne(folder); 
	}
	 

	 
}

void sjh::tool_vcmd::vDir(vssd & MyVssd, std::wstring & DirCommand)
{
	std::vector<std::wstring> Dirs;
	sjh::vssd_tool::split(DirCommand, Dirs, L" ");
	for (int i = 0; i < Dirs.size(); i++)
	{
		tool_path a;
		sjh::vssd_folder * Folder = v_FindPath(MyVssd, Dirs[i], a);
		if (!Folder) {
			std::cout << "VSSD ERROR : This folder is not exist! " << std::endl; continue;
		}
		if (Folder->isFile()) {
			std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
			return;
		} 
		else {
			Folder->ShowOffSub(0, a.FoldersToPath());
		}
	 
	
	}
	  
			 
}

sjh::vssd_folder * sjh::tool_vcmd::v_FindPath(vssd & MyVssd, std::wstring & PathCommand, tool_path &aPath)
{
	sjh::vssd_foldertop *MyTop = MyVssd.GetNowTop();
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
	for (int i = 0; i < path.Folders.size(); i++)
	{
		//说明是磁盘开头，则为绝对路径
		if (flag_tofirstif && path.Folders[i].length() == 2 && path.Folders[i].at(1) == ':') {
			Nowpath.Folders.clear(); 
			Nowpath.RealFolders.clear();
			Nowpath.Folders.push_back(L"");
			Nowpath.SetRealpath(MyVssd.GetGenius(),0) ; 
			 
			longNowf = Nowpath.GetNow()->Find(path.Folders[i]);
			
			
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
			 
			longNowf = longNowf->Find(path.Folders[i]);
			if (!longNowf) {

				return nullptr;
			}
			Nowpath.AddOne(longNowf);
			if (longNowf->VssdTypeCode == 2 && i + 1 == path.Folders.size()) { aPath = Nowpath; return longNowf; }
			 

			
			 
			while(longNowf->VssdTypeCode == 2) longNowf = longNowf->SubFolders[0];
		}

	}
	 
	aPath = Nowpath;
	return longNowf;
	 
	 
}

void sjh::tool_vcmd::vCd(vssd & MyVssd, std::wstring & CdCommand)
{
	tool_path a;
	sjh::vssd_folder * folder = v_FindPath(MyVssd, CdCommand, a);
	if (folder && folder->isFile()) {
		std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
		return;
	}
	 
	if (folder && ((folder->VssdTypeCode != 2) ||(folder->VssdTypeCode == 2 && folder->SubFolders[0]))) {
		MyVssd.GetNowTop()->NowPath = a; 
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
		  

					 
	  
}

//改名--目前路径
void sjh::tool_vcmd::vRen(vssd & MyVssd, std::wstring & renCommand) {

	


	if (!MyVssd.GetNowTop()->NowPath.RealFolders.at(MyVssd.GetNowTop()->NowPath.RealFolders.size() - 2)->Find(renCommand)) {
		if (MyVssd.GetNowTop()->GetNowPos()->GetName().compare(MyVssd.GetNowTop()->root->GetName()) != 0)
			MyVssd.GetNowTop()->GetNowPos()->SetName(renCommand);
	}
	else {
		std::cout << "VSSD ERROR : The folder has already existed! " << std::endl;

	}
	
}

void sjh::tool_vcmd::vRen(vssd & MyVssd, std::wstring & SrcCommand, std::wstring & DesName) {
	tool_path a;
	sjh::vssd_folder * folder = v_FindPath(MyVssd, SrcCommand, a);
	if (folder && a.Folders.size() > 2 && !(a.RealFolders.at(a.RealFolders.size()-2)->Find(DesName))) {
		folder->SetName(DesName);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
	 
}

int sjh::tool_vcmd::vMd(vssd & MyVssd, std::wstring & mdCommand)
{
	tool_path a;

	sjh::vssd_folder * folder = v_FindPath(MyVssd, mdCommand, a);
	 
	vssd_tool::Trim(mdCommand);
	if (!folder)    {
		a.PathToFolders(mdCommand);
		if (a.Folders[0].length() > 1 && a.Folders[0].at(1) != ':') {
			MyVssd.GetNowTop()->GetNowPos()->Build(MyVssd,a);
		}
		else {
			MyVssd.GetGenius()->Build(MyVssd,a);
		}
		return 0;
		 
	}
	else {
		return 1;
	}
	 
	 
	
}
//移动文件夹
void sjh::tool_vcmd::vMove(vssd & MyVssd, std::wstring & Src, std::wstring & Des) {

	tool_path a;
	tool_path b;
	sjh::vssd_folder * Srcfolder = v_FindPath(MyVssd, Src, a);
	sjh::vssd_folder * disfolder = v_FindPath(MyVssd, Des, b);
	if (!Srcfolder) { std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return; }
	if (!Srcfolder) { std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;  return; }
	if (Srcfolder->isFile()) {
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vCopy(MyVssd, Src, Des);
		return;
	}
	if (Srcfolder && disfolder && a.Folders.size() >= 3 && b.Folders.size() >= 2) {
		a.RealFolders.at(a.RealFolders.size() - 2)->OffOne(Srcfolder);
		disfolder->VssdFolderLink(Srcfolder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

	 

}

void sjh::tool_vcmd::vMove(vssd & MyVssd, std::wstring & Des) {

	tool_path b;
	sjh::vssd_folder * disfolder = v_FindPath(MyVssd, Des, b); 
	if (disfolder) {
		disfolder->VssdFolderLink(MyVssd.GetNowTop()->GetNowPos());
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}

void sjh::tool_vcmd::vCls()
{
	system("cls");
}

void sjh::tool_vcmd::v_jump(vssd & MyVssd, std::wstring & JumpTo)
{
	sjh::vssd_foldertop* Top = MyVssd.FindTop(JumpTo);
	MyVssd.SetNowTop(Top);
}

void sjh::tool_vcmd::vSave(vssd & MyVssd, std::wstring & JumpTo)
{
	
	MyVssd.Serialize(MyVssd.Serial);
	 
	std::ofstream Vssdfile(JumpTo, std::ios::binary);
	if (Vssdfile.is_open())
	{
		std::wstring data;
		vssd_tool::GetStringAnd0(MyVssd.Serial,0, MyVssd.Serial.size(),data); 
		 
		Vssdfile.write((const char*)&data[0],data.size()); 
		
		Vssdfile.close();
		MyVssd.Serial.clear();
	}
	else {
		std::cout << "Error opening file";
	}

	
	//获取文件指针
	//FILE *file= nullptr;  
	//MyVssd.puttoRealfile(file);
}

void sjh::tool_vcmd::vLoad(vssd & MyVssd, std::wstring & GetFrom)
{
	MyVssd.Serial.clear();
	char ch;
	std::ifstream Vssdfile(GetFrom, std::ios::binary);
	if (!Vssdfile.is_open())
	{
		std::cout << "Error opening file"; exit(1);
	}
	while (!Vssdfile.eof())
	{
		char ch = ' ';

		

		for (int i = 0; i < 36; i++)
		{
			Vssdfile.read(&ch, 1);
			MyVssd.Serial.push_back(ch);
		}
		unsigned int Bytelength = 0;
		vssd_tool::Get4BUint(MyVssd.Serial, 32, Bytelength);

		for (int i = 0; i < Bytelength-36; i++)
		{
			Vssdfile.read(&ch, 1);
			MyVssd.Serial.push_back(ch);
		}

		Vssdfile.close();
	 
		 
	} 
	//获取文件指针
	//FILE *file;
	//MyVssd.GetFromRealfile(file);
	MyVssd.DeSerialize(MyVssd.Serial); 
	MyVssd.Serial.clear();
}

void sjh::tool_vcmd::vDel(vssd & MyVssd, std::wstring & DelCommand)
{
	tool_path a;
	sjh::vssd_folder * folder = v_FindPath(MyVssd, DelCommand, a);
	if (folder && a.Folders.size() >= 3) {
		a.RealFolders.at(a.RealFolders.size() - 2)->DeletOne(folder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}

void sjh::tool_vcmd::vCopy(vssd & MyVssd, std::wstring & Src, std::wstring & Des)
{
	tool_path a;
	tool_path b;
	sjh::vssd_folder * Srcfolder = v_FindPath(MyVssd, Src, a);
	sjh::vssd_folder * disfolder = v_FindPath(MyVssd, Des, b);
	if (Srcfolder && disfolder && a.Folders.size() >= 3 && b.Folders.size() >= 2) {
		a.RealFolders.at(a.RealFolders.size() - 2)->OffOne(Srcfolder);
		disfolder->VssdFolderLink(Srcfolder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}

void sjh::tool_vcmd::vMklink(vssd & MyVssd, std::wstring & Src, std::wstring & LinkName)
{
	tool_path a; 
	//找到需要指向的文件夹
	sjh::vssd_folder * Srcfolder = v_FindPath(MyVssd, Src, a); 
	
	if (Srcfolder && a.Folders.size() >= 3 ) {
		//找到之后
		if (vMd(MyVssd, LinkName)) {
			return;
		}
		


		//创建Link文件
		sjh::vssd_folder *Link = MyVssd.GetNowTop()->GetNowPos()->Find(LinkName);
		 
		Link->VssdTypeCode = 2;
		 //找到创建的Link文件
		Link->VssdFolderLink(Srcfolder);
		//将Link文件第一个子文件放入指向文件
		Srcfolder->AddLink(Link);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}

void sjh::tool_vcmd::v_cmd_comein(vssd & MyVssd, std::wstring & CmdCommand)
{
	sjh::vssd_foldertop *MyTop = MyVssd.GetNowTop();
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
			std::wstring reardis = rear.substr(spacePos + 1, rear.length() - spacePos);

			vCopy(MyVssd, rearSrc, reardis);

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
	  
}

 