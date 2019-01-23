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


	//按照文档上的格式保存二进制


}

void sjh::vssd::GetFromRealfile(FILE * d)
{
	//按照文档上的格式读取二进制
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
	//调用Top的de方法，创建Top数组，返回指针Tops

	sjh::vssd_folder *GeniusNow = new sjh::vssd_folder(L"",0); 
	//调用folder的de方法，递归创建folder
	GeniusNow->deSerialize(ByteVssd, foldertablepoint);


	Genius = GeniusNow;
	 
	Tops.clear();
	for (int i = 0; i < Genius->SubFolders.size(); i++)
	{
		sjh::vssd_foldertop *pan = new sjh::vssd_foldertop(Genius->SubFolders[i], Genius);
		Tops.push_back(pan);
	}

	SetNowTop(Tops[Tops.size()-1]);

	 



	//析构Vssd里的全部属性，保留本身


	//建立与新属性的链接，并赋值给Vssd的NowTop和Tops

	 

}

void sjh::vssd::Serialize(std::vector<unsigned char> &ByteVssd) {
	
	//Vssd预完成，需要填充指针		48
	{
	//Name
	sjh::vssd_tool::PushString(Name, ByteVssd);
	sjh::vssd_tool::Push0ToNSpace(32 - Name.length(), ByteVssd);
	//Top指针指向index0 和 预留Top表指针4字节
	sjh::vssd_tool::Push4BUint(0, ByteVssd);
	sjh::vssd_tool::Push0ToNSpace(4, ByteVssd);
	// Genius index = 0 和 固定folder表指针48位置
	sjh::vssd_tool::Push4BUint(0, ByteVssd);
	sjh::vssd_tool::Push4BUint(52, ByteVssd);
	//预留content表指针4字节
	sjh::vssd_tool::Push0ToNSpace(4, ByteVssd);
	}

	std::vector<unsigned char> *Byte_foldertable = new std::vector<unsigned char>();

	std::vector<unsigned char> *Byte_contenttable = new std::vector<unsigned char>();;

	int index = 0;
	//folder表和content表预完成，需要填充Subfolder指针    folder表紧接着放到ByteVssd后面（48的位置）
	{
		Genius->Serialize(*Byte_foldertable, *Byte_contenttable,index); 

	}
	int ToptablePos = Byte_foldertable->size() + 52;
	std::vector<unsigned char>::iterator it = ByteVssd.begin();
	it += 36;
	sjh::vssd_tool::Set4BUint(it, ToptablePos);


	//通过Find来填充Subfolder指针 
	{

	}


	std::vector<unsigned char> *Byte_Toptable = new std::vector<unsigned char>();
	//获取Top表，
	//表数据放入具体位置
	//table s放入ByteVssd中 完善ByteVssd表的指向，folder表中content指向  
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
	//返回一个std::vector<unsigned char> &Byte_foldertable;
	//获取内容表std::vector<unsigned char> &Byte_contenttable;

	 



}

sjh::vssd::~vssd()
{

}
