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
	//�����ĵ��ϵĸ�ʽ���������
}

void vssd::getfromrealfile(FILE * d)
{
	//�����ĵ��ϵĸ�ʽ��ȡ������
}
void vssd::deserialize(std::vector<unsigned char> &byte_vssd) {
	std::string dname = SPACE32;
	std::vector<unsigned char>::iterator it = byte_vssd.begin();
	
	vssd_tool::popstring(dname, 32, it);
	
	//��ȡfolder��ͨ���ݹ鴴��


	//

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
	it1 += 44;
	vssd_tool::set4Buint(it, contenttablepos);
	 

	vssd_tool::copyappend(byte_foldertable, byte_vssd);

	vssd_tool::copyappend(byte_toptable, byte_vssd);

	vssd_tool::copyappend(byte_contenttable, byte_vssd);

	//����һ��std::vector<unsigned char> &byte_foldertable;
	//��ȡ���ݱ�std::vector<unsigned char> &byte_contenttable;

	
	


	

	



}

vssd::~vssd()
{

}
