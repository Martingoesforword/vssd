#include "pch.h"   


sjh::vssd_pan * sjh::vssd_disk::GetNooowPan()
{
	return NowPan;
}
sjh::vssd_Inode * sjh::vssd_disk::GetGenius()
{
	return Genius;
}
void sjh::vssd_disk::SetNooowPan(sjh::vssd_pan * aInodeTop)
{
	NowPan = aInodeTop;
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

sjh::vssd_disk::vssd_disk(sjh::vssd_pan * Now, sjh::vssd_Inode * aGenius, std::wstring aName):base_namedable(aName)
{
	NowPan = Now; 
	Genius = aGenius;
}

sjh::vssd_disk* sjh::vssd_disk::CreateVssd()
{

	sjh::vssd_Inode *Genius = new sjh::vssd_Inode(L"", sjh::vssd_Inode::IS_FOLDER);
	sjh::vssd_Inode *c_pan = new sjh::vssd_Inode(L"C:", sjh::vssd_Inode::IS_FOLDER);
	 
	sjh::vssd_Inode *Folder = new sjh::vssd_Inode(L"sjh", sjh::vssd_Inode::IS_FOLDER);
	sjh::vssd_Inode *File = new sjh::vssd_Inode(L"sjh.txt", sjh::vssd_Inode::IS_FILE);
	c_pan->LoadOneSub(Folder);
	c_pan->LoadOneSub(File);
	sjh::vssd_pan *MyTopcpan = new sjh::vssd_pan(c_pan, Genius);//¼ÓÔØ¸ùÄ¿Â¼
	sjh::vssd_disk *MyVssd = new sjh::vssd_disk(MyTopcpan, Genius, L"firstVssd");

	MyVssd->AddNewPan(MyTopcpan); 

	Genius->LoadOneSub(c_pan);
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

	sjh::vssd_Inode *GeniusNow = new sjh::vssd_Inode(L"", sjh::vssd_Inode::IS_FOLDER);
	GeniusNow->DeSerialize(ByteVssd, Pos);


	Pans.clear();
	for (size_t i = 0; i < GeniusNow->GetSubInodes().size(); i++)
	{
		sjh::vssd_pan *pan = new sjh::vssd_pan(GeniusNow->GetSubInodes()[i], GeniusNow);
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

sjh::vssd_Inode *sjh::vssd_disk::BuildPath(sjh::vssd_Inode *NowFolder , sjh::tool_path &aPath, int aType)
{
	if (aPath.IsAbsolutePath())
	{
		return BuildPath(GetGenius(), aPath, aType);
	}
	else if (NowFolder->IsLink())
	{
		return BuildPath(NowFolder->GetSubInodes()[0], aPath, aType);
	}
	else if (NowFolder->IsFolder())
	{
		sjh::vssd_Inode *Now = NowFolder;
		bool CheckedFlag = true;

		for (size_t i = 0; i < aPath.Inodes.size(); i++)
		{
			 
			int Result = 0;
			Result = Now->FindSelfSubForFirst(aPath.Inodes[i], 0);
			if (CheckedFlag && Result != Now->NOT_FINDED)
			{ 
				Now = Now->GetSubInodes()[Result]->FindFolderByLink();  
				CheckedFlag = false;
			}
			else
			{
				sjh::vssd_Inode *f1 = new sjh::vssd_Inode(aPath.Inodes[i], aType);
				Now->LoadOneSub(f1);
				Now = f1;
			}

		}
		return Now;
	}
	else {
		return nullptr;
	}


}