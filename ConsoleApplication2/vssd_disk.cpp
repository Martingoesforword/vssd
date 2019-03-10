#include "pch.h"  
#include "vssd_disk.h"
namespace sjh { 
	vssd_pan * VirtualDisk::GetNooowPan() const
	{
		return NowPan;
	} 
	vssd_inode * VirtualDisk::GetGenius() const
	{
		return Genius;
	}
	 
	
	void VirtualDisk::SetNooowPan(vssd_pan * aInodeTop)
	{
		NowPan = aInodeTop;
	}
	 

	 

	void VirtualDisk::AddNewPan(vssd_pan * aNowTop)
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

	
	VirtualDisk::VirtualDisk(vssd_pan * Now, vssd_inode * aGenius, std::wstring aName) :Name(vssd_name(aName)), NowPan(Now), Genius(aGenius)
	{  
	}

	


	vssd_pan * VirtualDisk::FindPanFromName(const std::wstring & aName)
	{
		for (size_t i = 0; i < Pans.size(); i++)
		{
			if ((aName == Pans[i]->GetRoot()->GetName()) )
			{
				return Pans[i];
			}
		}
		return nullptr;

	}


	void VirtualDisk::SetName(std::wstring aName)
	{
		
		Name.Set(aName);
	}

	const std::wstring & VirtualDisk::GetName()
	{
		return Name.Get();
	}






	size_t VirtualDisk::Serialize(std::vector<wchar_t> &ByteVssd)
	{

		tool::string::PushString(GetName(), ByteVssd);
		Genius->Serialize(ByteVssd);
		return ByteVssd.size();
	}

	void VirtualDisk::DeSerialize(std::vector<wchar_t>& ByteVssd, int &Pos)
	{

		SetName(tool::string::GetString(ByteVssd, Pos));

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

	VirtualDisk::~VirtualDisk()
	{
		delete Genius;
		for (size_t i = 0; i < Pans.size(); i++)
		{
			delete Pans[i];
		}

	}

	void VirtualDisk::Display()
	{
		std::wcout << L"<VirtualDisk class>" << std::endl;
	}

	vssd_inode *VirtualDisk::BuildPath(VirtualDisk & vd,vssd_inode *NowFolder, tools_path &aPath, int aType)
	{
		
		if (NowFolder->IsLinkD())
		{
			return BuildPath(vd,NowFolder->GetSubInodes()[0], aPath, aType);
		}
		else if (NowFolder->IsFolder())
		{
			vssd_inode *Now = NowFolder;
			bool CheckedFlag = true;
			int a = 0;
			if (aPath.Inodes[0] == L"\\") { a = 1; Now = vd.GetNooowPan()->GetRoot(); }
			for (size_t i = a; i < aPath.Inodes.size(); i++)
			{

				size_t Result = 0;
				Result = Now->FindSelfSubForNext(aPath.Inodes[i], 0);
				if (CheckedFlag && vssd_inode::IsFinded(Result))
				{
					Now = vssd_optcmd::CheckLink(vd,Now->GetSubInodes()[Result]);
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