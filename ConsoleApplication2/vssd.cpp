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


	//�����ĵ��ϵĸ�ʽ���������


}

void vssd::getfromrealfile(FILE * d)
{
	//�����ĵ��ϵĸ�ʽ��ȡ������
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
	//����top��de����������top���飬����ָ��tops

	vssd_folder *geniusnow = new vssd_folder("",0); 
	//����folder��de�������ݹ鴴��folder
	geniusnow->deserialize(byte_vssd, foldertablepoint);


	genius = geniusnow;
	 
	tops.clear();
	for (int i = 0; i < genius->subfolders.size(); i++)
	{
		vssd_foldertop *pan = new vssd_foldertop(genius->subfolders[i], genius);
		tops.push_back(pan);
	}

	setnowtop(tops[tops.size()-1]);

	 



	//����vssd���ȫ�����ԣ���������


	//�����������Ե����ӣ�����ֵ��vssd��nowtop��tops

	 

}

void vssd::serialize(std::vector<unsigned char> &byte_vssd) {
	
	//vssdԤ��ɣ���Ҫ���ָ��		48
	{
	//name
	vssd_tool::pushstring(name, byte_vssd);
	vssd_tool::push0toNspace(32 - name.length(), byte_vssd);
	//topָ��ָ��index0 �� Ԥ��top��ָ��4�ֽ�
	vssd_tool::push4Buint(0, byte_vssd);
	vssd_tool::push0toNspace(4, byte_vssd);
	// genius index = 0 �� �̶�folder��ָ��48λ��
	vssd_tool::push4Buint(0, byte_vssd);
	vssd_tool::push4Buint(52, byte_vssd);
	//Ԥ��content��ָ��4�ֽ�
	vssd_tool::push0toNspace(4, byte_vssd);
	}

	static std::vector<unsigned char> byte_foldertable; 

	static std::vector<unsigned char> byte_contenttable;

	int index = 0;
	//folder���content��Ԥ��ɣ���Ҫ���subfolderָ��    folder������ŷŵ�byte_vssd���棨48��λ�ã�
	{
		genius->serialize(byte_foldertable, byte_contenttable,index); 

	}
	int toptablepos = byte_foldertable.size() + 52;
	std::vector<unsigned char>::iterator it = byte_vssd.begin();
	it += 36;
	vssd_tool::set4Buint(it, toptablepos);


	//ͨ��find�����subfolderָ�� 
	{

	}


	static std::vector<unsigned char> byte_toptable;
	//��ȡtop��
	//�����ݷ������λ��
	//table s����byte_vssd�� ����byte_vssd���ָ��folder����contentָ��  
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
	//����һ��std::vector<unsigned char> &byte_foldertable;
	//��ȡ���ݱ�std::vector<unsigned char> &byte_contenttable;

	
	


	

	



}

vssd::~vssd()
{

}
