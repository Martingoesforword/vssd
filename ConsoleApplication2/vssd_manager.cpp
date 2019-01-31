#include "vssd_manager.h"
namespace sjh { 
	vssd_pan * vssd_manager::GetNooowPan()
	{
		return NowPan;
	}
	vssd_inode * vssd_manager::GetGenius()
	{
		return Genius;
	}
	vssd_vcmd * vssd_manager::GetVcmd()
	{
		return &Vcmd;
	}
	void vssd_manager::SetNooowPan(vssd_pan * aInodeTop)
	{
		NowPan = aInodeTop;
	}
	 

	void vssd_manager::AddNewPan(vssd_pan * aNowTop)
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

	void vssd_manager::ComeInVcmd()
	{
		Vcmd.TypeCode_UI();
		return;
	}

	vssd_manager::vssd_manager(vssd_pan * Now, vssd_inode * aGenius, std::wstring aName) :base_namedable(aName)
	{
		Vcmd = *(new vssd_vcmd());
		NowPan = Now;
		Genius = aGenius;
	}

	vssd_manager* vssd_manager::CreateVssd()
	{

		vssd_inode *Genius = new vssd_inode(L"", vssd_inode::IS_FOLDER);
		vssd_inode *c_pan = new vssd_inode(L"C:", vssd_inode::IS_FOLDER);

		vssd_inode *Folder = new vssd_inode(L"sjh", vssd_inode::IS_FOLDER);
		vssd_inode *File = new vssd_inode(L"sjh.txt", vssd_inode::IS_FILE);
		c_pan->LoadOneSub(Folder);
		c_pan->LoadOneSub(File);
		vssd_pan *MyTopcpan = new vssd_pan(c_pan, Genius);//¼ÓÔØ¸ùÄ¿Â¼
		vssd_manager *MyVssd = new vssd_manager(MyTopcpan, Genius, L"firstVssd");

		MyVssd->AddNewPan(MyTopcpan);

		Genius->LoadOneSub(c_pan);
		return MyVssd;
	}


	vssd_pan * vssd_manager::FindPanFromName(std::wstring & aName)
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





	int vssd_manager::Serialize(std::vector<wchar_t> &ByteVssd)
	{

		tool::stringtools::PushString(GetName(), ByteVssd);
		Genius->Serialize(ByteVssd);
		return ByteVssd.size();
	}

	void vssd_manager::DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos)
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

	vssd_manager::~vssd_manager()
	{

	}

	void vssd_manager::Display()
	{
		std::wcout << L"<vssd_manager class>" << std::endl;
	}

	vssd_inode *vssd_manager::BuildPath(vssd_inode *NowFolder, tools_path &aPath, int aType)
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