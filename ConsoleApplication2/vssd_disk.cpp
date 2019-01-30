#include "pch.h"   


sjh::vssd_pan * sjh::vssd_disk::GetNooowPan()
{
	return NowPan;
}
sjh::vssd_folder * sjh::vssd_disk::GetGenius()
{
	return Genius;
}
void sjh::vssd_disk::SetNooowPan(sjh::vssd_pan * afolderTop)
{
	NowPan = afolderTop;
}



void sjh::vssd_disk::AddNewPan(sjh::vssd_pan * aNowTop)
{
	if (Pans.size() == 0)
	{
		NowPan = aNowTop;
	}
	if (Pans.size() < Pans.max_size())
	{
		Pans.push_back(aNowTop);
	}

}

sjh::vssd_disk::vssd_disk(sjh::vssd_pan * Now, sjh::vssd_folder * aGenius, std::wstring aName):base_namedable(aName)
{
	NowPan = Now; 
	Genius = aGenius;
}

sjh::vssd_disk* sjh::vssd_disk::CreateVssd()
{

	sjh::vssd_folder *Genius = new sjh::vssd_folder(L"", sjh::vssd_folder::IS_FOLDER);
	sjh::vssd_folder *c_pan = new sjh::vssd_folder(L"C:", sjh::vssd_folder::IS_FOLDER);
	 
	sjh::vssd_folder *folder = new sjh::vssd_folder(L"sjh", sjh::vssd_folder::IS_FOLDER);
	c_pan->AddOneSub(folder);
	sjh::vssd_pan *MyTopcpan = new sjh::vssd_pan(c_pan, Genius);//¼ÓÔØ¸ùÄ¿Â¼
	sjh::vssd_disk *MyVssd = new sjh::vssd_disk(MyTopcpan, Genius, L"firstVssd");

	MyVssd->AddNewPan(MyTopcpan); 

	Genius->AddOneSub(c_pan);
	return MyVssd;
}

 
sjh::vssd_pan * sjh::vssd_disk::FindPanFromName(std::wstring & aName)
{
	for (size_t i = 0; i < Pans.size(); i++)
	{
		if (aName.compare(Pans[i]->GetRoot()->GetName()) == IS_SAMESTRING)
		{
			return Pans[i];
		}
	}
	return nullptr;

}

 

 

int sjh::vssd_disk::Serialize(std::vector<wchar_t> &ByteVssd)
{ 
	
	sjh::tools_vssd::PushString(GetName(), ByteVssd); 
	Genius->Serialize(ByteVssd);  
	return ByteVssd.size();
}

void sjh::vssd_disk::DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos)
{
	 
	SetName(sjh::tools_vssd::GetString(ByteVssd, Pos));

	sjh::vssd_folder *GeniusNow = new sjh::vssd_folder(L"", sjh::vssd_folder::IS_FOLDER);
	GeniusNow->DeSerialize(ByteVssd, Pos);


	Pans.clear();
	for (size_t i = 0; i < GeniusNow->GetSubFolders().size(); i++)
	{
		sjh::vssd_pan *pan = new sjh::vssd_pan(GeniusNow->GetSubFolders()[i], GeniusNow);
		Pans.push_back(pan);
	}


	SetNooowPan(Pans[Pans.size() - 1]);
	Genius = GeniusNow;
}

sjh::vssd_disk::~vssd_disk()
{

}

void sjh::vssd_disk::Display()
{
	std::wcout << L"<vssd_disk class>" <<  std::endl;
}
