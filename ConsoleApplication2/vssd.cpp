#include "pch.h"  
 
 
vssd_foldertop * vssd::getnowtop()
{
	return nowtop;
}
vssd_folder * vssd::getgenius()
{
	return genius;
}
void vssd::setnowtop(vssd_foldertop * afoldertop)
{
	nowtop = afoldertop;
}
 
 

void vssd::linktop(vssd_foldertop * anowtop)
{
	if (tops.size() == 0) {
		nowtop = anowtop;
	}
	if (tops.size() < tops.max_size()) {
		tops.push_back(anowtop);  
	}
	
}

vssd::vssd(vssd_foldertop * Now, vssd_folder * agenius, std::string aname)
{
	nowtop = Now;
	name = aname;
	genius = agenius;
}
 
 
vssd::vssd()
{
	
}
 
vssd_foldertop * vssd::findtop(std::string & aname)
{
	for (int i = 0; i < tops.size(); i++)
	{
		if (aname == tops[i ]-> root->getname() ) {
			return tops[i];
		}
	}
	return nullptr; 
}

void vssd::puttorealfile(FILE * d)
{
	//按照文档上的格式保存二进制
}

void vssd::getfromrealfile(FILE * d)
{
	//按照文档上的格式读取二进制
}

void vssd::serialize(std::vector<unsigned char> &byte) {
	
	//数据长度
	vssd_tool::push(0, byte);
	unsigned int lengthpoint = byte.size() - 4;


	//数据内容



}

vssd::~vssd()
{

}
