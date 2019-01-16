#include "pch.h" 

//�����ļ�����dir
void tool_vcmd::vdir(vssd_foldertop * top)
{
	
	top->getnowposition()->showoffsub();
}
//�����ļ�����cd
void tool_vcmd::vcd(vssd_foldertop * mytop) 
{

	mytop->shownowposition();
}
//�����ļ�����rd
void tool_vcmd::vrd(vssd & myvssd) {
	if (myvssd.getnowtop()->nowpath.realfolders.size() >= 3) {
		myvssd.getnowtop()->nowpath.realfolders.at(myvssd.getnowtop()->nowpath.realfolders.size() - 2)->deletone(myvssd.getnowtop()->getnowposition());

		myvssd.getnowtop()->nowpath.deletone(); 
		std::cout << "VSSD ERROR : Nowposition folder is deleted just��" << std::endl;
	}
	else {
		std::cout << "VSSD ERROR : Root folder cannot be deleted��" << std::endl;
	}
	

}

void tool_vcmd::vrd(vssd & myvssd, std::string & rdcommand)
{
	tool_path a;
	vssd_folder * folder = v_findpath(myvssd, rdcommand, a);
	if (folder->isFile()) {
		std::cout << "VSSD WORRING : Please use 'del filename' next time!" << std::endl;
		vdel(myvssd, rdcommand);
		return;
	}
	if (folder && a.folders.size() >= 3) {
		a.realfolders.at(a.realfolders.size() - 2)->deletone(folder); 
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

	 
}

void tool_vcmd::vdir(vssd & myvssd, std::string & dircommand)
{
	tool_path a;
	vssd_folder * folder = v_findpath(myvssd, dircommand,a);
	if (folder->isFile()) {
		std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
		return;
	}
	if (folder) {
		folder->showoffsub();
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
			
	  
			 
}

vssd_folder * tool_vcmd::v_findpath(vssd & myvssd, std::string & pathcommand, tool_path &apath)
{
	vssd_foldertop *mytop = myvssd.getnowtop();
	static tool_path nowpath;
	nowpath = mytop->nowpath;//Ŀǰλ��
	//nowpath
	std::string pathstring = pathcommand;
	vssd_tool::trim(&pathstring); 
	tool_path path;
	path.pathtofolders(pathstring);
	//path��pathstring
	vssd_folder * longnowf = nowpath.getnow();	

	int flag_tofirstif = 1;
	for (int i = 0; i < path.folders.size(); i++)
	{
		//˵���Ǵ��̿�ͷ����Ϊ����·��
		if (flag_tofirstif && path.folders[i].length() == 2 && path.folders[i].at(1) == ':') {
			nowpath.folders.clear(); 
			nowpath.realfolders.clear();
			nowpath.folders.push_back("");
			nowpath.setrealpath(myvssd.getgenius(),0) ; 
			longnowf = nowpath.getnow()->find(path.folders[i]);
			if (!longnowf) {
				return nullptr;
			}
			nowpath.addone(longnowf);
			flag_tofirstif = 0;
		}
		else if (path.folders.at(i)== "..") {
			if (nowpath.realfolders.size() < 3) {
				return nullptr;
			}
			else {
				nowpath.deletone();
			}

		}
		else if (path.folders.at(i)== ".") {

		}
		//·���з�'n:' '..' '.'
		else {
			longnowf = longnowf->find(path.folders[i]);
			if (!longnowf) {
				return nullptr;
			}
			nowpath.addone(longnowf);
		}

	}

	apath = nowpath;
	return longnowf;
	 
	 
}

void tool_vcmd::vcd(vssd & myvssd, std::string & cdcommand)
{
	tool_path a;
	vssd_folder * folder = v_findpath(myvssd, cdcommand, a);
	if (folder && folder->isFile()) {
		std::cout << "VSSD ERROR : This folder is not exist!" << std::endl;
		return;
	}
	if (folder) {
		myvssd.getnowtop()->nowpath = a; 
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
		  

					 
	  
}

//����--Ŀǰ·��
void tool_vcmd::vren(vssd & myvssd, std::string & rencommand) {

	


	if (!myvssd.getnowtop()->nowpath.realfolders.at(myvssd.getnowtop()->nowpath.realfolders.size() - 2)->find(rencommand)) {
		if (myvssd.getnowtop()->getnowposition()->getname() != myvssd.getnowtop()->root->getname())
			myvssd.getnowtop()->getnowposition()->setname(rencommand);
	}
	else {
		std::cout << "VSSD ERROR : The folder has already existed! " << std::endl;

	}
	
}

void tool_vcmd::vren(vssd & myvssd, std::string & srccommand, std::string & disname) {
	tool_path a;
	vssd_folder * folder = v_findpath(myvssd, srccommand, a);
	if (folder && a.folders.size() > 2 && !(a.realfolders.at(a.realfolders.size()-2)->find(disname))) {
		folder->setname(disname);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
	 
}

void tool_vcmd::vmd(vssd & myvssd, std::string & mdcommand)
{
	tool_path a;

	vssd_folder * folder = v_findpath(myvssd, mdcommand, a);
	 
	
	
	if (!folder) {
		a.pathtofolders(mdcommand);
		if (a.folders[0].length() > 1 && a.folders[0].at(1) != ':') {
			myvssd.getnowtop()->getnowposition()->build(myvssd,a);
		}
		else {
			myvssd.getgenius()->build(myvssd,a);
		}
		 
	}
	 
	 
	
}
//�ƶ��ļ���
void tool_vcmd::vmove(vssd & myvssd, std::string & src, std::string & dis) {

	tool_path a;
	tool_path b;
	vssd_folder * srcfolder = v_findpath(myvssd, src, a);
	vssd_folder * disfolder = v_findpath(myvssd, dis, b);
	if (srcfolder->isFile()) {
		std::cout << "VSSD WORRING : Please use 'del filename' next time!" << std::endl;
		vcopy(myvssd, src, dis);
		return;
	}
	if (srcfolder && disfolder && a.folders.size() >= 3 && b.folders.size() >= 2) {
		a.realfolders.at(a.realfolders.size() - 2)->offone(srcfolder);
		disfolder->vssd_folder_link(srcfolder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

	 

}

void tool_vcmd::vmove(vssd & myvssd, std::string & dis) {

	tool_path b;
	vssd_folder * disfolder = v_findpath(myvssd, dis, b); 
	if (disfolder) {
		disfolder->vssd_folder_link(myvssd.getnowtop()->getnowposition());
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}

void tool_vcmd::vcls()
{
	system("cls");
}

void tool_vcmd::v_jump(vssd & myvssd, std::string & jumpto)
{
	vssd_foldertop* top = myvssd.findtop(jumpto);
	myvssd.setnowtop(top);
}

void tool_vcmd::vsave(vssd & myvssd, std::string & jumpto)
{
	//��ȡ�ļ�ָ��
	//FILE *file;  
	//myvssd.puttorealfile(file);
}

void tool_vcmd::vload(vssd & myvssd, std::string & jumpto)
{
	//��ȡ�ļ�ָ��
	//FILE *file;
	//myvssd.getfromrealfile(file);
}

void tool_vcmd::vdel(vssd & myvssd, std::string & delcommand)
{
	tool_path a;
	vssd_folder * folder = v_findpath(myvssd, delcommand, a);
	if (folder && a.folders.size() >= 3) {
		a.realfolders.at(a.realfolders.size() - 2)->deletone(folder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}

}

void tool_vcmd::vcopy(vssd & myvssd, std::string & src, std::string & dis)
{
	tool_path a;
	tool_path b;
	vssd_folder * srcfolder = v_findpath(myvssd, src, a);
	vssd_folder * disfolder = v_findpath(myvssd, dis, b);
	if (srcfolder && disfolder && a.folders.size() >= 3 && b.folders.size() >= 2) {
		a.realfolders.at(a.realfolders.size() - 2)->offone(srcfolder);
		disfolder->vssd_folder_link(srcfolder);
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}

void tool_vcmd::vmklink(vssd & myvssd, std::string & src, std::string & linkname)
{
	tool_path a; 
	//�ҵ���Ҫָ����ļ���
	vssd_folder * srcfolder = v_findpath(myvssd, src, a); 

	if (srcfolder && a.folders.size() >= 3 ) {
		//�ҵ�֮��
		vmd(myvssd, linkname);



		//����link�ļ�
		vssd_folder *link = myvssd.getnowtop()->getnowposition()->find(linkname);
		link->vssdtypecode = 2;
		 //�ҵ�������link�ļ�
		link->vssd_folder_link(srcfolder);
		//��link�ļ���һ�����ļ�����ָ���ļ�
	}
	else {
		std::cout << "VSSD ERROR : This folder is not exist! " << std::endl;
	}
}

 
void tool_vcmd::comein(vssd & myvssd, std::string & cmdcommand)
{
	vssd_foldertop *mytop = myvssd.getnowtop();
	vssd_tool::trim(cmdcommand);
	std::string rear;

	//�������������������
	if (cmdcommand.length() == 0) {
			
	}
	//dir�������
	else if (cmdcommand.length() >= 3 && cmdcommand.substr(0,3).compare("dir") == 0) {			
		if (cmdcommand.length() == 3) {
			vdir(mytop);
		}
		else {
			rear = cmdcommand.substr(3, cmdcommand.length() - 3);
			vssd_tool::trim(rear);
			vdir(myvssd,rear);
		}
		
	}
	//del�������
	else if (cmdcommand.length() >= 3 && cmdcommand.substr(0, 3).compare("del") == 0) {
		 
		rear = cmdcommand.substr(3, cmdcommand.length() - 3);
		vssd_tool::trim(rear);
		vdel(myvssd, rear);
		 

	}
	//save�������
	else if (cmdcommand.length() > 4 && cmdcommand.substr(0, 4).compare("save") == 0) {


		rear = cmdcommand.substr(4, cmdcommand.length() - 4);
		vssd_tool::trim(rear);
		 
		vsave(myvssd, rear);

	}
	//mklink�������
	else if (cmdcommand.length() > 6 && cmdcommand.substr(0, 6).compare("mklink") == 0) {

		rear = cmdcommand.substr(6, cmdcommand.length() - 6);
		int spacepos = rear.find(" ", 1);
		if (spacepos != -1) {

			std::string rearsrc = rear.substr(0, spacepos);
			std::string reardisname = rear.substr(spacepos + 1, rear.length() - spacepos);

			vmklink(myvssd, rearsrc, reardisname);

		}
		 

		 

	}
	//cd�������
	else if (cmdcommand.length() >= 2 && cmdcommand.substr(0, 2).compare("cd") == 0) {
		if (cmdcommand.length() == 2) {
			vcd(mytop);
		}
		else {
			rear = cmdcommand.substr(2, cmdcommand.length() - 2);
			vssd_tool::trim(rear);
			vcd(myvssd, rear);
		}

	} 
	//rd�������
	else if (cmdcommand.length() >= 2 && cmdcommand.substr(0, 2).compare("rd") == 0) {
		if (cmdcommand.length() == 2) {
			vrd(myvssd);
		}
		else {
			rear = cmdcommand.substr(2, cmdcommand.length() - 2);
			vssd_tool::trim(rear);
			vrd(myvssd, rear);
		}

	}
	//ren�������
	else if (cmdcommand.length() > 3 && cmdcommand.substr(0, 3).compare("ren") == 0) {
		
		 

		rear = cmdcommand.substr(3, cmdcommand.length() - 3);
		int spacepos = rear.find(" ", 1);
		if (spacepos != -1) {

			std::string rearsrc = rear.substr(0, spacepos);
			std::string reardisname = rear.substr(spacepos + 1, rear.length() - spacepos);
			  
			vren(myvssd, rearsrc, reardisname);

		}
		else {
			std::string rearsrc = rear;
			vssd_tool::trim(rear);
			vren(myvssd, rear);
		}
		
		 
		//����
		//0123456789
		//023203 323

	}
	//copy�������
	else if (cmdcommand.length() > 4 && cmdcommand.substr(0, 4).compare("copy") == 0) {


		rear = cmdcommand.substr(4, cmdcommand.length() - 4);
		vssd_tool::trim(rear);
		int spacepos = rear.find(" ", 0);
		if (spacepos != -1) {

			std::string rearsrc = rear.substr(0, spacepos);
			std::string reardis = rear.substr(spacepos + 1, rear.length() - spacepos);

			vcopy(myvssd, rearsrc, reardis);

		}
		 
		 

	}
	//move�������
	else if (cmdcommand.length() > 4 && cmdcommand.substr(0, 4).compare("move") == 0) {

		 
		rear = cmdcommand.substr(4, cmdcommand.length() - 4);
		vssd_tool::trim(rear);
		int spacepos = rear.find(" ", 0);
		if (spacepos != -1) {

			std::string rearsrc = rear.substr(0, spacepos);
			std::string reardis = rear.substr(spacepos + 1, rear.length() - spacepos);
			 
			vmove(myvssd, rearsrc, reardis);

		}
		else {
			std::string reardis = rear;
			vssd_tool::trim(rear);
			vmove(myvssd, reardis);
		}


		//����
		//0123456789
		//023203 323

	}
	//��ת���������
	else if (cmdcommand.length() == 2 && cmdcommand.at(1) == ':') {
		rear = cmdcommand;
		v_jump(myvssd, rear);
	}
	//�����������
	else if (cmdcommand.length() == 3 && cmdcommand.compare("cls") == 0) {
		vcls();
	}
	//�����ļ����������
	else if (cmdcommand.length() > 2 && cmdcommand.substr(0, 2).compare("md") == 0) {
		 
		rear = cmdcommand.substr(2, cmdcommand.length() - 2);
		vssd_tool::trim(rear);
		vmd(myvssd, rear);

	}
	  
}


tool_vcmd::tool_vcmd()
{
}


tool_vcmd::~tool_vcmd()
{
}
