#include "vssd_disk.h"
namespace sjh { 
	vssd_pan * vssd_disk::GetNooowPan()
	{
		return NowPan;
	}
	vssd_inode * vssd_disk::GetGenius()
	{
		return Genius;
	}
	
	void vssd_disk::SetNooowPan(vssd_pan * aInodeTop)
	{
		NowPan = aInodeTop;
	}
	 

	void vssd_disk::AddNewPan(vssd_pan * aNowTop)
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

	
	vssd_disk::vssd_disk(vssd_pan * Now, vssd_inode * aGenius, std::wstring aName) :base_namedable(aName)
	{
		
		NowPan = Now;
		Genius = aGenius;
	}

	


	vssd_pan * vssd_disk::FindPanFromName(std::wstring & aName)
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





	int vssd_disk::Serialize(std::vector<wchar_t> &ByteVssd)
	{

		tool::stringtools::PushString(GetName(), ByteVssd);
		Genius->Serialize(ByteVssd);
		return ByteVssd.size();
	}

	void vssd_disk::DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos)
	{

		SetName(tool::stringtools::GetString(ByteVssd, Pos));

		vssd_inode *GeniusNow = new vssd_inode(L"", vssd_inode::IS_FOLDER);
		GeniusNow->DeSerialize(ByteVssd, Pos);


		Pans.clear();
		for (size_t i = 0; i < GeniusNow->GetSubInodes().size(); i++)
		{
			vssd_pan *pan = new vssd_pan(GeniusNow->GetSubInodes()[i], GeniusNow);
			Pans.push_back(pan);
		}


		SetNooowPan(Pans[Pans.size() - 1]);
		Genius = GeniusNow;
	}

	vssd_disk::~vssd_disk()
	{

	}

	void vssd_disk::Display()
	{
		std::wcout << L"<vssd_disk class>" << std::endl;
	}

	vssd_inode *vssd_disk::BuildPath(vssd_inode *NowFolder, tools_path &aPath, int aType)
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
			vssd_inode *Now = NowFolder;
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
					vssd_inode *f1 = new vssd_inode(aPath.Inodes[i], aType);
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
}