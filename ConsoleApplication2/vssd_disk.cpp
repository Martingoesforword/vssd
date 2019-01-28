#include "pch.h"  


sjh::vssd_pan * sjh::vssd_disk::GetNowTop()
{
	return NowTop;
}
sjh::vssd_folder * sjh::vssd_disk::GetGenius()
{
	return Genius;
}
void sjh::vssd_disk::SetNowTop(sjh::vssd_pan * afolderTop)
{
	NowTop = afolderTop;
}



void sjh::vssd_disk::LinkTop(sjh::vssd_pan * aNowTop)
{
	if (Tops.size() == 0)
	{
		NowTop = aNowTop;
	}
	if (Tops.size() < Tops.max_size())
	{
		Tops.push_back(aNowTop);
	}

}

sjh::vssd_disk::vssd_disk(sjh::vssd_pan * Now, sjh::vssd_folder * aGenius, std::wstring aName)
{
	NowTop = Now;
	Name = aName;
	Genius = aGenius;
}

sjh::vssd_disk* sjh::vssd_disk::CreatVssd()
{

	sjh::vssd_folder *Genius = new sjh::vssd_folder(L"", sjh::vssd_folder::IS_FOLDER);
	sjh::vssd_folder *c_pan = new sjh::vssd_folder(L"c:", sjh::vssd_folder::IS_FOLDER);
	 
 
	sjh::vssd_pan *MyTopcpan = new sjh::vssd_pan(c_pan, Genius);//���ظ�Ŀ¼
	sjh::vssd_disk *MyVssd = new sjh::vssd_disk(MyTopcpan, Genius, L"firstVssd");

	MyVssd->LinkTop(MyTopcpan);
	  
	Genius->VssdFolderLink(c_pan);
	return MyVssd;
}


sjh::vssd_disk::vssd_disk()
{

}

sjh::vssd_pan * sjh::vssd_disk::FindTop(std::wstring & aName)
{
	for (size_t i = 0; i < Tops.size(); i++)
	{
		if (aName.compare(Tops[i]->root->GetName()) == 0)
		{
			return Tops[i];
		}
	}
	return nullptr;

}

void sjh::vssd_disk::PutToRealFile(FILE * d)
{


	//�����ĵ��ϵĸ�ʽ���������


}

void sjh::vssd_disk::GetFromRealfile(FILE * d)
{
	//�����ĵ��ϵĸ�ʽ��ȡ������
}
void sjh::vssd_disk::DeSerialize(std::vector<wchar_t> &ByteVssd)
{

	std::vector<wchar_t>::iterator it = ByteVssd.begin();

	sjh::tools_vssd::GetString(ByteVssd, 0, 32, Name);
	unsigned int Topindex = 0;
	sjh::tools_vssd::Get4BUint(ByteVssd, 32, Topindex);
	unsigned int Toptablepoint = 0;
	sjh::tools_vssd::Get4BUint(ByteVssd, 36, Toptablepoint);
	unsigned int Geniusindex = 0;
	sjh::tools_vssd::Get4BUint(ByteVssd, 40, Geniusindex);
	unsigned int foldertablepoint = 0;
	sjh::tools_vssd::Get4BUint(ByteVssd, 44, foldertablepoint);
	unsigned int contenttablepoint = 0;
	sjh::tools_vssd::Get4BUint(ByteVssd, 48, contenttablepoint);
	//����Top��de����������Top���飬����ָ��Tops

	sjh::vssd_folder *GeniusNow = new sjh::vssd_folder(L"", 0);
	//����folder��de�������ݹ鴴��folder
	GeniusNow->deSerialize(ByteVssd, foldertablepoint);


	Genius = GeniusNow;

	Tops.clear();
	for (size_t i = 0; i < Genius->SubFolders.size(); i++)
	{
		sjh::vssd_pan *pan = new sjh::vssd_pan(Genius->SubFolders[i], Genius);
		Tops.push_back(pan);
	}

	SetNowTop(Tops[Tops.size() - 1]);





	//����Vssd���ȫ�����ԣ���������


	//�����������Ե����ӣ�����ֵ��Vssd��NowTop��Tops



}

void sjh::vssd_disk::Serialize(std::vector<wchar_t> &ByteVssd)
{

	//VssdԤ��ɣ���Ҫ���ָ��		48
	{
		//Name
		sjh::tools_vssd::PushString(Name, ByteVssd);
		sjh::tools_vssd::Push0ToNSpace(32 - Name.length(), ByteVssd);
		//Topָ��ָ��index0 �� Ԥ��Top��ָ��4�ֽ�
		sjh::tools_vssd::Push4BUint(0, ByteVssd);
		sjh::tools_vssd::Push0ToNSpace(4, ByteVssd);
		// Genius index = 0 �� �̶�folder��ָ��48λ��
		sjh::tools_vssd::Push4BUint(0, ByteVssd);
		sjh::tools_vssd::Push4BUint(52, ByteVssd);
		//Ԥ��content��ָ��4�ֽ�
		sjh::tools_vssd::Push0ToNSpace(4, ByteVssd);
	}

	std::vector<wchar_t> *Byte_foldertable = new std::vector<wchar_t>();

	std::vector<wchar_t> *Byte_contenttable = new std::vector<wchar_t>();;

	int index = 0;
	//folder���content��Ԥ��ɣ���Ҫ���Subfolderָ��    folder������ŷŵ�ByteVssd���棨48��λ�ã�
	{
		Genius->Serialize(*Byte_foldertable, *Byte_contenttable, index);

	}
	int ToptablePos = Byte_foldertable->size() + 52;
	std::vector<wchar_t>::iterator it = ByteVssd.begin();
	it += 36;
	sjh::tools_vssd::Set4BUint(it, ToptablePos);


	//ͨ��Find�����Subfolderָ�� 
	{

	}


	std::vector<wchar_t> *Byte_Toptable = new std::vector<wchar_t>();
	//��ȡTop��
	//�����ݷ������λ��
	//table s����ByteVssd�� ����ByteVssd���ָ��folder����contentָ��  
	{
		for (size_t i = 0; i < Tops.size(); i++)
		{
			Tops.at(i)->Serialize(*Byte_Toptable);
		}
	}



	int contenttablePos = ToptablePos + Byte_Toptable->size();
	std::vector<wchar_t>::iterator it1 = ByteVssd.begin();
	it1 += 48;
	sjh::tools_vssd::Set4BUint(it1, contenttablePos);


	sjh::tools_vssd::CopyAppend(*Byte_foldertable, ByteVssd);

	sjh::tools_vssd::CopyAppend(*Byte_Toptable, ByteVssd);

	sjh::tools_vssd::CopyAppend(*Byte_contenttable, ByteVssd);

	sjh::tools_vssd::Push4BUintForPos(contenttablePos + Byte_contenttable->size(), 32, ByteVssd);
	//����һ��std::vector<wchar_t> &Byte_foldertable;
	//��ȡ���ݱ�std::vector<wchar_t> &Byte_contenttable;





}

sjh::vssd_disk::~vssd_disk()
{

}
