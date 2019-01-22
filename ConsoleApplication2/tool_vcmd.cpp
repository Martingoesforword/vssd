#include "pch.h" 

//�����ļ�����dir
void sjh::tool_vcmd::vDir(sjh::vssd_foldertop * Top)
{
	sjh::vssd_folder *now = Top->GetNowPos();
	if(now->VssdTypeCode != 2) now->ShowOffSub();
	else now->SubFolders[0]->ShowOffSub();
	 
}
//�����ļ�����cd
void sjh::tool_vcmd::vCd(sjh::vssd_foldertop * MyTop) 
{

	MyTop->ShowNowPos();
}
//�����ļ�����rd
void sjh::tool_vcmd::vRd(vssd & MyVssd) {
	if (MyVssd.GetNowTop()->NowPath.RealFolders.size() >= 3) {
		MyVssd.GetNowTop()->NowPath.RealFolders.at(MyVssd.GetNowTop()->NowPath.RealFolders.size() - 2)->DeletOne(MyVssd.GetNowTop()->GetNowPos());

		MyVssd.GetNowTop()->NowPath.DeletOne(); 
		std::cout << "VSSD ERROR : NowPos folder is deleted just��" << std::endl;
	}
	else {
		std::cout << "VSSD ERROR : Root folder cannot be deleted��" << std::endl;
	}
	

}

void sjh::tool_vcmd::vRd(vssd & MyVssd, std::string & rdCommand)
{
	tool_path a;
	sjh::vssd_folder * folder = v_FindPath(MyVssd, rdCommand, a);
	if (folder->isFile()) {
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vDel(MyVssd, rdCommand);
		return;
	}
	if (folder && a.Folders.size() >= 3) {
		a.RealFolders.at(a.RealFolders.size() - 2)->DeletOne(folder); 
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

	 
}

void sjh::tool_vcmd::vDir(vssd & MyVssd, std::string & DirCommand)
{
	tool_path a;
	sjh::vssd_folder * Folder = v_FindPath(MyVssd, DirCommand,a);
	if (Folder->isFile()) {
		std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
		return;
	}
	if (Folder) {
		Folder->ShowOffSub();
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
			
	  
			 
}

sjh::vssd_folder * sjh::tool_vcmd::v_FindPath(vssd & MyVssd, std::string & pathCommand, tool_path &apath)
{
	sjh::vssd_foldertop *MyTop = MyVssd.GetNowTop();
	static tool_path Nowpath;
	Nowpath = MyTop->NowPath;//Ŀǰλ��
	//Nowpath
	std::string pathstring = pathCommand;
	vssd_tool::Trim(&pathstring); 
	tool_path path;
	path.PathToFolders(pathstring);
	//path��pathstring
	sjh::vssd_folder * longNowf = Nowpath.GetNow();	

	int flag_tofirstif = 1;
	for (int i = 0; i < path.Folders.size(); i++)
	{
		//˵���Ǵ��̿�ͷ����Ϊ����·��
		if (flag_tofirstif && path.Folders[i].length() == 2 && path.Folders[i].at(1) == ':') {
			Nowpath.Folders.clear(); 
			Nowpath.RealFolders.clear();
			Nowpath.Folders.push_back("");
			Nowpath.SetRealpath(MyVssd.GetGenius(),0) ; 
			 
			longNowf = Nowpath.GetNow()->Find(path.Folders[i]);
			
			
			if (!longNowf) {
				return nullptr;
			}
			Nowpath.AddOne(longNowf);
			if (longNowf->VssdTypeCode == 2) longNowf = longNowf->SubFolders[0];
			flag_tofirstif = 0;
		}
		else if (path.Folders.at(i)== "..") {
			if (Nowpath.RealFolders.size() < 3) {
				return nullptr;
			}
			else {
				Nowpath.DeletOne();
			}

		}
		else if (path.Folders.at(i)== ".") {

		}
		//·���з�'n:' '..' '.'
		else {
			 
			longNowf = longNowf->Find(path.Folders[i]);
			if (!longNowf) {
				return nullptr;
			}
			Nowpath.AddOne(longNowf);
			if(longNowf->VssdTypeCode == 2) longNowf = longNowf->SubFolders[0];
		}

	}

	apath = Nowpath;
	return longNowf;
	 
	 
}

void sjh::tool_vcmd::vCd(vssd & MyVssd, std::string & cdCommand)
{
	tool_path a;
	sjh::vssd_folder * folder = v_FindPath(MyVssd, cdCommand, a);
	if (folder && folder->isFile()) {
		std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
		return;
	}
	if (folder) {
		MyVssd.GetNowTop()->NowPath = a; 
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
		  

					 
	  
}

//����--Ŀǰ·��
void sjh::tool_vcmd::vRen(vssd & MyVssd, std::string & renCommand) {

	


	if (!MyVssd.GetNowTop()->NowPath.RealFolders.at(MyVssd.GetNowTop()->NowPath.RealFolders.size() - 2)->Find(renCommand)) {
		if (MyVssd.GetNowTop()->GetNowPos()->GetName().compare(MyVssd.GetNowTop()->root->GetName()) != 0)
			MyVssd.GetNowTop()->GetNowPos()->SetName(renCommand);
	}
	else {
		std::cout << "VSSD ERROR : The folder has already existed! " << std::endl;

	}
	
}

void sjh::tool_vcmd::vRen(vssd & MyVssd, std::string & SrcCommand, std::string & disName) {
	tool_path a;
	sjh::vssd_folder * folder = v_FindPath(MyVssd, SrcCommand, a);
	if (folder && a.Folders.size() > 2 && !(a.RealFolders.at(a.RealFolders.size()-2)->Find(disName))) {
		folder->SetName(disName);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
	 
}

int sjh::tool_vcmd::vMd(vssd & MyVssd, std::string & mdCommand)
{
	tool_path a;

	sjh::vssd_folder * folder = v_FindPath(MyVssd, mdCommand, a);
	 
	 
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
//�ƶ��ļ���
void sjh::tool_vcmd::vMove(vssd & MyVssd, std::string & Src, std::string & dis) {

	tool_path a;
	tool_path b;
	sjh::vssd_folder * Srcfolder = v_FindPath(MyVssd, Src, a);
	sjh::vssd_folder * disfolder = v_FindPath(MyVssd, dis, b);
	if (Srcfolder->isFile()) {
		std::cout << "VSSD WORRING : Please use 'del fileName' next time!" << std::endl;
		vCopy(MyVssd, Src, dis);
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

void sjh::tool_vcmd::vMove(vssd & MyVssd, std::string & dis) {

	tool_path b;
	sjh::vssd_folder * disfolder = v_FindPath(MyVssd, dis, b); 
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

void sjh::tool_vcmd::v_jump(vssd & MyVssd, std::string & jumpto)
{
	sjh::vssd_foldertop* Top = MyVssd.FindTop(jumpto);
	MyVssd.SetNowTop(Top);
}

void sjh::tool_vcmd::vSave(vssd & MyVssd, std::string & jumpto)
{
	
	MyVssd.Serialize(MyVssd.Serial);
	 
	std::ofstream Vssdfile("d:\\Vssdfile", std::ios::binary);
	if (Vssdfile.is_open())
	{
		std::string data;
		vssd_tool::GetStringAnd0(MyVssd.Serial,0, MyVssd.Serial.size(),data); 
		 
		Vssdfile.write((const char*)&data[0],data.size()); 
		
		Vssdfile.close();
		MyVssd.Serial.clear();
	}
	else {
		std::cout << "Error opening file";
	}

	
	//��ȡ�ļ�ָ��
	//FILE *file= nullptr;  
	//MyVssd.puttoRealfile(file);
}

void sjh::tool_vcmd::vLoad(vssd & MyVssd, std::string & GetFrom)
{
	MyVssd.Serial.clear();
	char ch;
	std::ifstream Vssdfile("d:\\Vssdfile", std::ios::binary);
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
	//��ȡ�ļ�ָ��
	//FILE *file;
	//MyVssd.GetFromRealfile(file);
	MyVssd.DeSerialize(MyVssd.Serial); 
	MyVssd.Serial.clear();
}

void sjh::tool_vcmd::vDel(vssd & MyVssd, std::string & delCommand)
{
	tool_path a;
	sjh::vssd_folder * folder = v_FindPath(MyVssd, delCommand, a);
	if (folder && a.Folders.size() >= 3) {
		a.RealFolders.at(a.RealFolders.size() - 2)->DeletOne(folder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}

void sjh::tool_vcmd::vCopy(vssd & MyVssd, std::string & Src, std::string & dis)
{
	tool_path a;
	tool_path b;
	sjh::vssd_folder * Srcfolder = v_FindPath(MyVssd, Src, a);
	sjh::vssd_folder * disfolder = v_FindPath(MyVssd, dis, b);
	if (Srcfolder && disfolder && a.Folders.size() >= 3 && b.Folders.size() >= 2) {
		a.RealFolders.at(a.RealFolders.size() - 2)->OffOne(Srcfolder);
		disfolder->VssdFolderLink(Srcfolder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}

void sjh::tool_vcmd::vMklink(vssd & MyVssd, std::string & Src, std::string & LinkName)
{
	tool_path a; 
	//�ҵ���Ҫָ����ļ���
	sjh::vssd_folder * Srcfolder = v_FindPath(MyVssd, Src, a); 
	
	if (Srcfolder && a.Folders.size() >= 3 ) {
		//�ҵ�֮��
		if (vMd(MyVssd, LinkName)) {
			return;
		}
		


		//����Link�ļ�
		sjh::vssd_folder *Link = MyVssd.GetNowTop()->GetNowPos()->Find(LinkName);
		 
		Link->VssdTypeCode = 2;
		 //�ҵ�������Link�ļ�
		Link->VssdFolderLink(Srcfolder);
		//��Link�ļ���һ�����ļ�����ָ���ļ�
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}

 
void sjh::tool_vcmd::v_cmd_comein(vssd & MyVssd, std::string & CmdCommand)
{
	sjh::vssd_foldertop *MyTop = MyVssd.GetNowTop();
	vssd_tool::Trim(CmdCommand);
	std::string rear;

	//�������������������
	if (CmdCommand.length() == 0) {
			
	}
	//dir�������
	else if (CmdCommand.length() >= 3 && CmdCommand.substr(0,3).compare("dir") == 0) {			
		if (CmdCommand.length() == 3) {
			vDir(MyTop);
		}
		else {
			rear = CmdCommand.substr(3, CmdCommand.length() - 3);
			vssd_tool::Trim(rear);
			vDir(MyVssd,rear);
		}
		
	}
	//del�������
	else if (CmdCommand.length() >= 3 && CmdCommand.substr(0, 3).compare("del") == 0) {
		 
		rear = CmdCommand.substr(3, CmdCommand.length() - 3);
		vssd_tool::Trim(rear);
		vDel(MyVssd, rear);
		 

	}
	//save�������
	else if (CmdCommand.length() > 4 && CmdCommand.substr(0, 4).compare("save") == 0) {


		rear = CmdCommand.substr(4, CmdCommand.length() - 4);
		vssd_tool::Trim(rear);
		 
		vSave(MyVssd, rear);

	}
	//load�������
	else if (CmdCommand.length() > 4 && CmdCommand.substr(0, 4).compare("load") == 0) {


		rear = CmdCommand.substr(4, CmdCommand.length() - 4);
		vssd_tool::Trim(rear);

		vLoad(MyVssd, rear);

	}
	//mkLink�������
	else if (CmdCommand.length() > 6 && CmdCommand.substr(0, 6).compare("mklink") == 0) {

		rear = CmdCommand.substr(6, CmdCommand.length() - 6);
		int spacePos = rear.find(" ", 1);
		if (spacePos != -1) {

			std::string rearSrc = rear.substr(0, spacePos);
			std::string reardisName = rear.substr(spacePos + 1, rear.length() - spacePos);

			vMklink(MyVssd, rearSrc, reardisName);

		}
		 

		 

	}
	//cd�������
	else if (CmdCommand.length() >= 2 && CmdCommand.substr(0, 2).compare("cd") == 0) {
		if (CmdCommand.length() == 2) {
			vCd(MyTop);
		}
		else {
			rear = CmdCommand.substr(2, CmdCommand.length() - 2);
			vssd_tool::Trim(rear);
			vCd(MyVssd, rear);
		}

	} 
	//rd�������
	else if (CmdCommand.length() >= 2 && CmdCommand.substr(0, 2).compare("rd") == 0) {
		if (CmdCommand.length() == 2) {
			vRd(MyVssd);
		}
		else {
			rear = CmdCommand.substr(2, CmdCommand.length() - 2);
			vssd_tool::Trim(rear);
			vRd(MyVssd, rear);
		}

	}
	//ren�������
	else if (CmdCommand.length() > 3 && CmdCommand.substr(0, 3).compare("ren") == 0) {
		
		 

		rear = CmdCommand.substr(3, CmdCommand.length() - 3);
		int spacePos = rear.find(" ", 1);
		if (spacePos != -1) {

			std::string rearSrc = rear.substr(0, spacePos);
			std::string reardisName = rear.substr(spacePos + 1, rear.length() - spacePos);
			  
			vRen(MyVssd, rearSrc, reardisName);

		}
		else {
			std::string rearSrc = rear;
			vssd_tool::Trim(rear);
			vRen(MyVssd, rear);
		}
		
		 
		//����
		//0123456789
		//023203 323

	}
	//copy�������
	else if (CmdCommand.length() > 4 && CmdCommand.substr(0, 4).compare("copy") == 0) {


		rear = CmdCommand.substr(4, CmdCommand.length() - 4);
		vssd_tool::Trim(rear);
		int spacePos = rear.find(" ", 0);
		if (spacePos != -1) {

			std::string rearSrc = rear.substr(0, spacePos);
			std::string reardis = rear.substr(spacePos + 1, rear.length() - spacePos);

			vCopy(MyVssd, rearSrc, reardis);

		}
		 
		 

	}
	//move�������
	else if (CmdCommand.length() > 4 && CmdCommand.substr(0, 4).compare("move") == 0) {

		 
		rear = CmdCommand.substr(4, CmdCommand.length() - 4);
		vssd_tool::Trim(rear);
		int spacePos = rear.find(" ", 0);
		if (spacePos != -1) {

			std::string rearSrc = rear.substr(0, spacePos);
			std::string reardis = rear.substr(spacePos + 1, rear.length() - spacePos);
			 
			vMove(MyVssd, rearSrc, reardis);

		}
		else {
			std::string reardis = rear;
			vssd_tool::Trim(rear);
			vMove(MyVssd, reardis);
		}


		//����
		//0123456789
		//023203 323

	}
	//��ת���������
	else if (CmdCommand.length() == 2 && CmdCommand.at(1) == ':') {
		rear = CmdCommand;
		v_jump(MyVssd, rear);
	}
	//�����������
	else if (CmdCommand.length() == 3 && CmdCommand.compare("cls") == 0) {
		vCls();
	}
	//�����ļ����������
	else if (CmdCommand.length() > 2 && CmdCommand.substr(0, 2).compare("md") == 0) {
		 
		rear = CmdCommand.substr(2, CmdCommand.length() - 2);
		vssd_tool::Trim(rear);
		vMd(MyVssd, rear);

	}
	  
}

 