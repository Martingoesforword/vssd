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
	sjh::vssd_folder *c_pan = new sjh::vssd_folder(L"C:", sjh::vssd_folder::IS_FOLDER);
	 
	sjh::vssd_folder *folder = new sjh::vssd_folder(L"sjh", sjh::vssd_folder::IS_FOLDER);
	c_pan->VssdFolderLink(folder);
	sjh::vssd_pan *MyTopcpan = new sjh::vssd_pan(c_pan, Genius);//加载根目录
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

std::wstring sjh::vssd_disk::vssd_disk::GetName()
{
	return Name;
}

void sjh::vssd_disk::PutToRealFile(std::wstring JumpTo)
{

	unsigned int FileLength = Serial.size(); 
	std::ofstream Vssdfile(JumpTo, std::ios::binary);
	if (Vssdfile.is_open())
	{ 
		Vssdfile.write(((const char*)&FileLength) + 3, 1);
		Vssdfile.write(((const char*)&FileLength) + 2, 1);
		Vssdfile.write(((const char*)&FileLength) + 1, 1);
		Vssdfile.write((const char*)&FileLength, 1);  
		int pos = 0; 
		Vssdfile.write((const char*)&Serial[0], Serial.size() * 2);
		Vssdfile.close(); 
	}
	else
	{
		std::cout << "Error opening file";
	}
	//按照文档上的格式保存二进制


}

void sjh::vssd_disk::GetFromRealfile(std::wstring GetFrom)
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
		Serial.push_back(ch);
		ch = chp * 256 * 256 + chq;
		Serial.push_back(ch);

		unsigned int Bytelength = 0;
		int pos = 0;
		Bytelength = tools_vssd::GetLengthValue(Serial, pos);
		Serial.clear();

		for (size_t i = 0; i < Bytelength; i++)
		{
			Vssdfile.read(&chp, 1);
			Vssdfile.read(&chq, 1);

			wchar_t ch = chp + chq * 256 * 256;
			Serial.push_back(ch);
		}

		Vssdfile.close();


	}
	//按照文档上的格式读取二进制
}
void sjh::vssd_disk::DeSerialize(std::vector<wchar_t> &ByteVssd)
{
	int Pos = 0; 
	Name = sjh::tools_vssd::GetString(ByteVssd, Pos); 

	sjh::vssd_folder *GeniusNow = new sjh::vssd_folder(L"", sjh::vssd_folder::IS_FOLDER); 
	GeniusNow->deSerialize(ByteVssd, Pos);
	  

	Tops.clear();
	for (size_t i = 0; i < GeniusNow->SubFolders.size(); i++)
	{
		sjh::vssd_pan *pan = new sjh::vssd_pan(GeniusNow->SubFolders[i], GeniusNow);
		Tops.push_back(pan);
	}


	SetNowTop(Tops[Tops.size() - 1]); 
	Genius = GeniusNow;
	 


}

void sjh::vssd_disk::Serialize(std::vector<wchar_t> &ByteVssd)
{
	 
	sjh::tools_vssd::PushString(Name, ByteVssd); 
	Genius->Serialize(ByteVssd); 

}

sjh::vssd_disk::~vssd_disk()
{

}
