#include "pch.h"  
 
 
sjh::vssd_foldertop * sjh::vssd::GetNowTop()
{
	return NowTop;
}
sjh::vssd_folder * sjh::vssd::GetGenius()
{
	return Genius;
}
void sjh::vssd::SetNowTop(sjh::vssd_foldertop * afolderTop)
{
	NowTop = afolderTop;
}
 
 

void sjh::vssd::LinkTop(sjh::vssd_foldertop * aNowTop)
{
	if (Tops.size() == 0) {
		NowTop = aNowTop;
	}
	if (Tops.size() < Tops.max_size()) {
		Tops.push_back(aNowTop);  
	}
	
}

sjh::vssd::vssd(sjh::vssd_foldertop * Now, sjh::vssd_folder * aGenius, std::wstring aName)
{
	NowTop = Now;
	Name = aName;
	Genius = aGenius;
}
 
 
sjh::vssd::vssd()
{
	
}
 
sjh::vssd_foldertop * sjh::vssd::FindTop(std::wstring & aName)
{
	for (int i = 0; i < Tops.size(); i++)
	{
		if (aName.compare(Tops[i]-> root->GetName()) == 0 ) {
			return Tops[i];
		}
	}
	return nullptr;

}

void sjh::vssd::PutToRealFile(FILE * d)
{


	//�����ĵ��ϵĸ�ʽ���������


}

void sjh::vssd::GetFromRealfile(FILE * d)
{
	//�����ĵ��ϵĸ�ʽ��ȡ������
}
void sjh::vssd::DeSerialize(std::vector<unsigned char> &ByteVssd) {
	 
	std::vector<unsigned char>::iterator it = ByteVssd.begin();
	
	sjh::vssd_tool::GetString(ByteVssd, 0, 32, Name);  
	unsigned int Topindex = 0;
	sjh::vssd_tool::Get4BUint(ByteVssd, 32, Topindex);
	unsigned int Toptablepoint = 0;
	sjh::vssd_tool::Get4BUint(ByteVssd, 36, Toptablepoint);
	unsigned int Geniusindex = 0;
	sjh::vssd_tool::Get4BUint(ByteVssd, 40, Geniusindex);
	unsigned int foldertablepoint = 0;
	sjh::vssd_tool::Get4BUint(ByteVssd, 44, foldertablepoint);
	unsigned int contenttablepoint = 0;
	sjh::vssd_tool::Get4BUint(ByteVssd, 48, contenttablepoint);
	//����Top��de����������Top���飬����ָ��Tops

	sjh::vssd_folder *GeniusNow = new sjh::vssd_folder(L"",0); 
	//����folder��de�������ݹ鴴��folder
	GeniusNow->deSerialize(ByteVssd, foldertablepoint);


	Genius = GeniusNow;
	 
	Tops.clear();
	for (int i = 0; i < Genius->SubFolders.size(); i++)
	{
		sjh::vssd_foldertop *pan = new sjh::vssd_foldertop(Genius->SubFolders[i], Genius);
		Tops.push_back(pan);
	}

	SetNowTop(Tops[Tops.size()-1]);

	 



	//����Vssd���ȫ�����ԣ���������


	//�����������Ե����ӣ�����ֵ��Vssd��NowTop��Tops

	 

}

void sjh::vssd::Serialize(std::vector<unsigned char> &ByteVssd) {
	
	//VssdԤ��ɣ���Ҫ���ָ��		48
	{
	//Name
	sjh::vssd_tool::PushString(Name, ByteVssd);
	sjh::vssd_tool::Push0ToNSpace(32 - Name.length(), ByteVssd);
	//Topָ��ָ��index0 �� Ԥ��Top��ָ��4�ֽ�
	sjh::vssd_tool::Push4BUint(0, ByteVssd);
	sjh::vssd_tool::Push0ToNSpace(4, ByteVssd);
	// Genius index = 0 �� �̶�folder��ָ��48λ��
	sjh::vssd_tool::Push4BUint(0, ByteVssd);
	sjh::vssd_tool::Push4BUint(52, ByteVssd);
	//Ԥ��content��ָ��4�ֽ�
	sjh::vssd_tool::Push0ToNSpace(4, ByteVssd);
	}

	std::vector<unsigned char> *Byte_foldertable = new std::vector<unsigned char>();

	std::vector<unsigned char> *Byte_contenttable = new std::vector<unsigned char>();;

	int index = 0;
	//folder���content��Ԥ��ɣ���Ҫ���Subfolderָ��    folder������ŷŵ�ByteVssd���棨48��λ�ã�
	{
		Genius->Serialize(*Byte_foldertable, *Byte_contenttable,index); 

	}
	int ToptablePos = Byte_foldertable->size() + 52;
	std::vector<unsigned char>::iterator it = ByteVssd.begin();
	it += 36;
	sjh::vssd_tool::Set4BUint(it, ToptablePos);


	//ͨ��Find�����Subfolderָ�� 
	{

	}


	std::vector<unsigned char> *Byte_Toptable = new std::vector<unsigned char>();
	//��ȡTop��
	//�����ݷ������λ��
	//table s����ByteVssd�� ����ByteVssd���ָ��folder����contentָ��  
	{
		for (int i = 0; i < Tops.size(); i++)
		{
			Tops.at(i)->Serialize(*Byte_Toptable);
		} 
	}



	int contenttablePos = ToptablePos+ Byte_Toptable->size();
	std::vector<unsigned char>::iterator it1 = ByteVssd.begin();
	it1 += 48;
	sjh::vssd_tool::Set4BUint(it1, contenttablePos);
	 

	sjh::vssd_tool::CopyAppend(*Byte_foldertable, ByteVssd);

	sjh::vssd_tool::CopyAppend(*Byte_Toptable, ByteVssd);

	sjh::vssd_tool::CopyAppend(*Byte_contenttable, ByteVssd);

	sjh::vssd_tool::Push4BUintForPos(contenttablePos+ Byte_contenttable->size(), 32, ByteVssd);
	//����һ��std::vector<unsigned char> &Byte_foldertable;
	//��ȡ���ݱ�std::vector<unsigned char> &Byte_contenttable;

	 



}

sjh::vssd::~vssd()
{

}
