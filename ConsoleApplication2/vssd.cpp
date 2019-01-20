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
		if (aname.compare(tops[i]-> root->getname()) == 0 ) {
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
void vssd::deserialize(std::vector<unsigned char> &byte_vssd) {
	 
	std::vector<unsigned char>::iterator it = byte_vssd.begin();
	
	vssd_tool::getstring(byte_vssd, 0, 32, name);  
	unsigned int topindex = 0;
	vssd_tool::get4Buint(byte_vssd, 32, topindex);
	unsigned int toptablepoint = 0;
	vssd_tool::get4Buint(byte_vssd, 36, toptablepoint);
	unsigned int geniusindex = 0;
	vssd_tool::get4Buint(byte_vssd, 40, geniusindex);
	unsigned int foldertablepoint = 0;
	vssd_tool::get4Buint(byte_vssd, 44, foldertablepoint);
	unsigned int contenttablepoint = 0;
	vssd_tool::get4Buint(byte_vssd, 48, contenttablepoint);
	//调用top的de方法，创建top数组，返回指针tops

	vssd_folder *geniusnow = new vssd_folder("",0); 
	//调用folder的de方法，递归创建folder
	geniusnow->deserialize(byte_vssd, foldertablepoint);


	genius = geniusnow;
	 
	tops.clear();
	for (int i = 0; i < genius->subfolders.size(); i++)
	{
		vssd_foldertop *pan = new vssd_foldertop(genius->subfolders[i], genius);
		tops.push_back(pan);
	}

	setnowtop(tops[tops.size()-1]);

	 



	//析构vssd里的全部属性，保留本身


	//建立与新属性的链接，并赋值给vssd的nowtop和tops

	 

}

void vssd::serialize(std::vector<unsigned char> &byte_vssd) {
	
	//vssd预完成，需要填充指针		48
	{
	//name
	vssd_tool::pushstring(name, byte_vssd);
	vssd_tool::push0toNspace(32 - name.length(), byte_vssd);
	//top指针指向index0 和 预留top表指针4字节
	vssd_tool::push4Buint(0, byte_vssd);
	vssd_tool::push0toNspace(4, byte_vssd);
	// genius index = 0 和 固定folder表指针48位置
	vssd_tool::push4Buint(0, byte_vssd);
	vssd_tool::push4Buint(52, byte_vssd);
	//预留content表指针4字节
	vssd_tool::push0toNspace(4, byte_vssd);
	}

	static std::vector<unsigned char> byte_foldertable; 

	static std::vector<unsigned char> byte_contenttable;

	int index = 0;
	//folder表和content表预完成，需要填充subfolder指针    folder表紧接着放到byte_vssd后面（48的位置）
	{
		genius->serialize(byte_foldertable, byte_contenttable,index); 

	}
	int toptablepos = byte_foldertable.size() + 52;
	std::vector<unsigned char>::iterator it = byte_vssd.begin();
	it += 36;
	vssd_tool::set4Buint(it, toptablepos);


	//通过find来填充subfolder指针 
	{

	}


	static std::vector<unsigned char> byte_toptable;
	//获取top表，
	//表数据放入具体位置
	//table s放入byte_vssd中 完善byte_vssd表的指向，folder表中content指向  
	{
		for (int i = 0; i < tops.size(); i++)
		{
			tops.at(i)->serialize(byte_toptable);
		} 
	}



	int contenttablepos = toptablepos+ byte_toptable.size();
	std::vector<unsigned char>::iterator it1 = byte_vssd.begin();
	it1 += 48;
	vssd_tool::set4Buint(it1, contenttablepos);
	 

	vssd_tool::copyappend(byte_foldertable, byte_vssd);

	vssd_tool::copyappend(byte_toptable, byte_vssd);

	vssd_tool::copyappend(byte_contenttable, byte_vssd);

	vssd_tool::push4Buintforpos(contenttablepos+ byte_contenttable.size(), 32, byte_vssd);
	//返回一个std::vector<unsigned char> &byte_foldertable;
	//获取内容表std::vector<unsigned char> &byte_contenttable;

	
	


	

	



}

vssd::~vssd()
{

}
