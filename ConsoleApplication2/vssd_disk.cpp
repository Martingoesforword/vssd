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

sjh::vssd_disk* sjh::vssd_disk::CreatVssd()
{

	sjh::vssd_folder *Genius = new sjh::vssd_folder(L"", sjh::vssd_folder::IS_FOLDER);
	sjh::vssd_folder *c_pan = new sjh::vssd_folder(L"C:", sjh::vssd_folder::IS_FOLDER);
	 
	sjh::vssd_folder *folder = new sjh::vssd_folder(L"sjh", sjh::vssd_folder::IS_FOLDER);
	c_pan->AddOneSub(folder);
	sjh::vssd_pan *MyTopcpan = new sjh::vssd_pan(c_pan, Genius);//加载根目录
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

 
void sjh::vssd_disk::PutToRealFile(std::wstring JumpTo, std::vector<wchar_t> aSerial)
{

	unsigned int FileLength = aSerial.size(); 
	std::ofstream Vssdfile(JumpTo, std::ios::binary);
	if (Vssdfile.is_open())
	{ 
		Vssdfile.write(((const char*)&FileLength) + 3, 1);
		Vssdfile.write(((const char*)&FileLength) + 2, 1);
		Vssdfile.write(((const char*)&FileLength) + 1, 1);
		Vssdfile.write((const char*)&FileLength, 1);  
		int pos = 0; 
		Vssdfile.write((const char*)&aSerial[0], aSerial.size() * 2);
		Vssdfile.close(); 
	}
	else
	{
		std::cout << "Error opening file";
	}
	//按照文档上的格式保存二进制


}

void sjh::vssd_disk::GetFromRealfile(std::wstring GetFrom, std::vector<wchar_t> aSerial)
{
	std::ifstream Vssdfile(GetFrom, std::ios::binary);
	if (!Vssdfile.is_open())
	{
		std::cout << "Error opening file"; exit(1);
	}
	else
	{
		char chp = ' ';
		char chq = ' ';
		wchar_t ch;

		Vssdfile.read(&chp, 1);
		Vssdfile.read(&chq, 1);

		ch = chp * 256 * 256 + chq;
		Vssdfile.read(&chp, 1);
		Vssdfile.read(&chq, 1);
		aSerial.push_back(ch);
		ch = chp * 256 * 256 + chq;
		aSerial.push_back(ch);

		unsigned int Bytelength = 0;
		int pos = 0;
		Bytelength = tools_vssd::GetLengthValue(aSerial, pos);
		aSerial.clear();

		for (size_t i = 0; i < Bytelength; i++)
		{
			Vssdfile.read(&chp, 1);
			Vssdfile.read(&chq, 1);

			wchar_t ch = chp + chq * 256 * 256;
			aSerial.push_back(ch);
		}

		Vssdfile.close();


	}
	//按照文档上的格式读取二进制
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
	for (size_t i = 0; i < GeniusNow->SubFolders.size(); i++)
	{
		sjh::vssd_pan *pan = new sjh::vssd_pan(GeniusNow->SubFolders[i], GeniusNow);
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
