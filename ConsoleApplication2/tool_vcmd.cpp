#include "pch.h" 

//当下文件夹下dir
void tool_vcmd::vdir(vssd_foldertop * top)
{
	
	top->getnowposition()->showoffsub();
}
//当下文件夹下cd
void tool_vcmd::vcd(vssd_foldertop * mytop) 
{

	mytop->shownowposition();
}
//当下文件夹下rd
void tool_vcmd::vrd(vssd & myvssd) {
	if (myvssd.getnowtop()->nowpath.realfolders.size() >= 3) {
		myvssd.getnowtop()->nowpath.realfolders.at(myvssd.getnowtop()->nowpath.realfolders.size() - 2)->deletone(myvssd.getnowtop()->getnowposition());

		myvssd.getnowtop()->nowpath.deletone(); 
		std::cout << "VSSD ERROR : Nowposition folder is deleted just！" << std::endl;
	}
	else {
		std::cout << "VSSD ERROR : Root folder cannot be deleted！" << std::endl;
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
	nowpath = mytop->nowpath;//目前位置
	//nowpath
	std::string pathstring = pathcommand;
	vssd_tool::trim(&pathstring); 
	tool_path path;
	path.pathtofolders(pathstring);
	//path，pathstring
	vssd_folder * longnowf = nowpath.getnow();	

	int flag_tofirstif = 1;
	for (int i = 0; i < path.folders.size(); i++)
	{
		//说明是磁盘开头，则为绝对路径
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
		//路径中非'n:' '..' '.'
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

//改名--目前路径
void tool_vcmd::vren(vssd & myvssd, std::string & rencommand) {

	


	if (!myvssd.getnowtop()->nowpath.realfolders.at(myvssd.getnowtop()->nowpath.realfolders.size() - 2)->find(rencommand)) {
		if (myvssd.getnowtop()->getnowposition()->getname().compare(myvssd.getnowtop()->root->getname()) != 0)
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
	 
	
	
	if (!folder)    {
		a.pathtofolders(mdcommand);
		if (a.folders[0].length() > 1 && a.folders[0].at(1) != ':') {
			myvssd.getnowtop()->getnowposition()->build(myvssd,a);
		}
		else {
			myvssd.getgenius()->build(myvssd,a);
		}
		 
	}
	 
	 
	
}
//移动文件夹
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
	 
	myvssd.serialize(myvssd.serial);
	  
	std::ofstream vssdfile("d:\\vssdfile", std::ios::binary);
	if (vssdfile.is_open())
	{
		std::string data;
		vssd_tool::getstringand0(myvssd.serial,0, myvssd.serial.size(),data); 
		 
		vssdfile.write((const char*)&data[0],data.size()); 
		
		vssdfile.close();
		myvssd.serial.clear();
	}
	else {
		std::cout << "Error opening file";
	}

	
	//获取文件指针
	//FILE *file= nullptr;  
	//myvssd.puttorealfile(file);
}

void tool_vcmd::vload(vssd & myvssd, std::string & getfrom)
{
	myvssd.serial.clear();
	char ch;
	std::ifstream vssdfile("d:\\vssdfile", std::ios::binary);
	if (!vssdfile.is_open())
	{
		std::cout << "Error opening file"; exit(1);
	}
	while (!vssdfile.eof())
	{
		char ch = ' ';

		

		for (int i = 0; i < 36; i++)
		{
			vssdfile.read(&ch, 1);
			myvssd.serial.push_back(ch);
		}
		unsigned int bytelength = 0;
		vssd_tool::get4Buint(myvssd.serial, 32, bytelength);

		for (int i = 0; i < bytelength-36; i++)
		{
			vssdfile.read(&ch, 1);
			myvssd.serial.push_back(ch);
		}

		vssdfile.close();
	 
		 
	} 
	//获取文件指针
	//FILE *file;
	//myvssd.getfromrealfile(file);
	myvssd.deserialize(myvssd.serial); 
	myvssd.serial.clear();
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
	//找到需要指向的文件夹
	vssd_folder * srcfolder = v_findpath(myvssd, src, a); 

	if (srcfolder && a.folders.size() >= 3 ) {
		//找到之后
		vmd(myvssd, linkname);



		//创建link文件
		vssd_folder *link = myvssd.getnowtop()->getnowposition()->find(linkname);
		link->vssdtypecode = 2;
		 //找到创建的link文件
		link->vssd_folder_link(srcfolder);
		//将link文件第一个子文件放入指向文件
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

	//分析命令名与命令参数
	if (cmdcommand.length() == 0) {
			
	}
	//dir命令解析
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
	//del命令解析
	else if (cmdcommand.length() >= 3 && cmdcommand.substr(0, 3).compare("del") == 0) {
		 
		rear = cmdcommand.substr(3, cmdcommand.length() - 3);
		vssd_tool::trim(rear);
		vdel(myvssd, rear);
		 

	}
	//save命令解析
	else if (cmdcommand.length() > 4 && cmdcommand.substr(0, 4).compare("save") == 0) {


		rear = cmdcommand.substr(4, cmdcommand.length() - 4);
		vssd_tool::trim(rear);
		 
		vsave(myvssd, rear);

	}
	//load命令解析
	else if (cmdcommand.length() > 4 && cmdcommand.substr(0, 4).compare("load") == 0) {


		rear = cmdcommand.substr(4, cmdcommand.length() - 4);
		vssd_tool::trim(rear);

		vload(myvssd, rear);

	}
	//mklink命令解析
	else if (cmdcommand.length() > 6 && cmdcommand.substr(0, 6).compare("mklink") == 0) {

		rear = cmdcommand.substr(6, cmdcommand.length() - 6);
		int spacepos = rear.find(" ", 1);
		if (spacepos != -1) {

			std::string rearsrc = rear.substr(0, spacepos);
			std::string reardisname = rear.substr(spacepos + 1, rear.length() - spacepos);

			vmklink(myvssd, rearsrc, reardisname);

		}
		 

		 

	}
	//cd命令解析
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
	//rd命令解析
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
	//ren命令解析
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
		
		 
		//解释
		//0123456789
		//023203 323

	}
	//copy命令解析
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
	//move命令解析
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


		//解释
		//0123456789
		//023203 323

	}
	//跳转盘命令解析
	else if (cmdcommand.length() == 2 && cmdcommand.at(1) == ':') {
		rear = cmdcommand;
		v_jump(myvssd, rear);
	}
	//清屏命令解析
	else if (cmdcommand.length() == 3 && cmdcommand.compare("cls") == 0) {
		vcls();
	}
	//创建文件夹命令解析
	else if (cmdcommand.length() > 2 && cmdcommand.substr(0, 2).compare("md") == 0) {
		 
		rear = cmdcommand.substr(2, cmdcommand.length() - 2);
		vssd_tool::trim(rear);
		vmd(myvssd, rear);

	}
	  
}

 