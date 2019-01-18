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
void vssd::deserialize(std::vector<unsigned char> &byte_vssd) {
	std::string dname = SPACE32;
	std::vector<unsigned char>::iterator it = byte_vssd.begin();
	
	vssd_tool::popstring(dname, 32, it);
	
	//获取folder，通过递归创建


	//

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
	it1 += 44;
	vssd_tool::set4Buint(it, contenttablepos);
	 

	vssd_tool::copyappend(byte_foldertable, byte_vssd);

	vssd_tool::copyappend(byte_toptable, byte_vssd);

	vssd_tool::copyappend(byte_contenttable, byte_vssd);

	//返回一个std::vector<unsigned char> &byte_foldertable;
	//获取内容表std::vector<unsigned char> &byte_contenttable;

	
	


	

	



}

vssd::~vssd()
{

}
