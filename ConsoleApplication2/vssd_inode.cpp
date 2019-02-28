#include "pch.h"  
#include "vssd_inode.h" 
#include "tools_path.h"  
#include "vssd_disk.h"
namespace sjh {

	const std::wstring vssd_inode::VssdTypeName[4] = { L"FILE",L"DIR", L"SYMLINKD",L"SYMLINK" };


	std::wstring vssd_inode::GetTypeName() const
	{
		return VssdTypeName[InodeTypeCode];
	}

	vssd_inode::vssd_inode(std::wstring aName, int aCode) :Name(vssd_name(aName)), InodeTypeCode(aCode)
	{
	}
	 



	void vssd_inode::LoadOneSub(vssd_inode *LinktoSub )
	{
		
		if (IsFolder()) LinktoSub->SetFather(this);
		SubInodes.push_back(LinktoSub); 
	}




	void vssd_inode::PrintHead(std::wstring now) const
	{
		std::cout
			<< "\n " << tool::string::WStringToString(now) << " 的目录\n"
			<< std::endl;

	}
	void vssd_inode::PrintOTP() const
	{
		std::cout
			<< tool::string::WStringToString(tool::string::GetTimeWString(Content.GetTime()))
			<< "    "
			<< std::setiosflags(std::ios::right)
			<< "<" << tool::string::WStringToString(GetTypeName()) << ">"
			<< std::setfill(' ') << std::setw(10) << " "
			<< "."
			<< std::endl;
		std::cout
			<< tool::string::WStringToString(tool::string::GetTimeWString(GetFather()->Content.GetTime()))
			<< "    "
			<< std::setiosflags(std::ios::right)
			<< "<" << tool::string::WStringToString(GetFather()->GetTypeName()) << ">"
			<< std::setfill(' ')
			<< std::setw(10)
			<< " "
			<< ".."
			<< std::endl;

	}
	void vssd_inode::PrintFileInfo()
	{
		std::cout
			<< tool::string::GetTimeString(Content.GetTime())
			<< "    "
			<< std::setfill(' ') << std::setw(14) << tool::string::GetSizeString((unsigned int)Content.Size() * sizeof(unsigned char))
			<< " " << tool::string::WStringToString(GetName())
			<< std::endl;
	}
	void vssd_inode::PrintFoLiInfo()
	{
		std::cout
			<< tool::string::GetTimeString(Content.GetTime()) << "    "
			<< std::setiosflags(std::ios::right)
			<< "<" << tool::string::WStringToString(GetTypeName()) << ">"
			<< std::setfill(' ') << std::setw(10) << " "
			<< tool::string::WStringToString(GetName())
			<< std::endl;
	}

	void vssd_inode::SetLinkPath(std::wstring PathWString)
	{
		LinkPath->SetInodesByWstring(PathWString);
	}

	void vssd_inode::SetLinkPath(tools_path& Path)
	{
		LinkPath = &Path;
	}

	void vssd_inode::SetName(std::wstring aName)
	{
		Name.Set(aName);
	}

	const std::wstring & vssd_inode::GetName() const
	{
		return Name.Get();
	}
	//bool comp(const vssd_inode* a, const vssd_inode* b) {
	//	return a->GetName() < b->GetName();
	//}
	void vssd_inode::PrintAllSub(int pram, std::wstring now) const
	{

		PrintHead(now);
		PrintOTP();
		//std::sort(SubInodes.begin(), SubInodes.end(), comp);
		for (size_t i = 0; i < SubInodes.size(); i++)
		{
			if (SubInodes[i]->IsFile())
			{
				SubInodes[i]->PrintFileInfo();
			}
			else {
				SubInodes[i]->PrintFoLiInfo();
			}
		}

		if (pram == DIR_TYPE_TREE)
		{
			for (size_t i = 0; i < SubInodes.size(); i++)
			{
				if (SubInodes[i]->IsLinkF()) {}
				if (SubInodes[i]->IsFile())
				{
					PrintHead(now);
					SubInodes[i]->PrintFileInfo();
				}
				else
				{

					std::wstring a = now;
					if (a[a.size() - 1] != '\\') a.append(L"\\");
					a.append(SubInodes[i]->GetName());
					vssd_inode* aa = SubInodes[i];
					while (aa->IsLinkD()) aa = aa->GetSubInodes()[0];
					aa->PrintAllSub(pram, a);
				}

			}
		}

	}
	void vssd_inode::DeleteTreeFiles()
	{
		for (size_t i = SubInodes.size(); i >= 1; i--)
		{
			if (SubInodes[i-1]->IsFolder())
			{
				SubInodes[i - 1]->DeleteTreeFiles();
			}
			else if (SubInodes[i - 1]->IsFile() || SubInodes[i- 1]->IsLinkF())
			{
				DeleteOneSub(SubInodes[i -1]);
			}
		}
	}
	void vssd_inode::DeleteFiles()
	{
		for (size_t i = SubInodes.size(); i >= 1; i--)
		{
			if (SubInodes[i - 1]->IsFile() || SubInodes[i - 1]->IsLinkF())
			{
				delete SubInodes.at(i - 1);
				SubInodes.erase(SubInodes.begin() + i - 1);
			}
		}
	}
	void vssd_inode::DeleteOneSub(vssd_inode * deletInode)
	{
		for (size_t i = 0; i < SubInodes.size(); i++)
		{
			if ((SubInodes.at(i)->GetName() == deletInode->GetName()))
			{
				delete SubInodes.at(i);
				SubInodes.erase(SubInodes.begin() + i);
				return;
			}
		}
	}
	void vssd_inode::DeleteOneLink(vssd_inode * deletInode)
	{
		for (size_t i = 0; i < SubInodes.size(); i++)
		{
			if ((SubInodes.at(i)->GetName() == deletInode->GetName()))
			{
				delete SubInodes.at(i);
				SubInodes.erase(SubInodes.begin() + i);
				return;
			}
		}
	}
	void vssd_inode::UnloadOneSub(vssd_inode * deletInode)
	{
		size_t j = 0;
		for (size_t i = 0; i < SubInodes.size(); i++)
		{

			for (; j < SubInodes.max_size(); j++)
			{
				if (SubInodes.at(j) == NULL)
				{
					continue;
				}
				else
				{
					break;
				}
			}

			if ((SubInodes.at(j)->GetName() == deletInode->GetName()))
			{
				std::vector<vssd_inode*>::iterator it = SubInodes.begin();
				SubInodes.erase(it + j);
				return;
			}
			else
			{
				j++;
			}

		}
	}

	void vssd_inode::DeleteAllFile()
	{
		 
		for (size_t i = 0; i < SubInodes.size(); i++)
		{
			if (SubInodes[i]->IsFile())
			{
				delete SubInodes[i];
			} 
			else if(SubInodes[i]->IsFolder())
			{
				SubInodes[i]->DeleteAllFile();
			}
			else if (SubInodes[i]->IsLinkD())
			{
				SubInodes[i]->LinkPath->RealInodes[SubInodes[i]->LinkPath->RealInodes.size() - 1]->DeleteAllFile();
			}
		}
		if (IsFile())
		{
			delete this;
		}
	}

	void vssd_inode::DeleteWholeTree()
	{
		size_t j = 0;
		for (size_t i = 0; i < SubInodes.size(); i++)
		{

			for (; j < SubInodes.max_size(); j++)
			{
				if (SubInodes.at(j) == NULL)
				{
					continue;
				}
				else
				{
					SubInodes.at(j)->DeleteWholeTree();
					SubInodes.at(j)->~vssd_inode();
					break;
				}
			}


			j++;


		}
	}



	int vssd_inode::FindSelfSubForNext(std::wstring& Inode, size_t StartIndex) const
	{
		for (size_t i = StartIndex; i < SubInodes.size(); i++)
		{
			if (SubInodes.at(i) != NULL)
			{
				if (tool::string::WStringMatch(SubInodes.at(i)->GetName(), Inode) != 0)
				{
					return (int)i;
				}
				if (i > SubInodes.size())
				{
					break;
				}
			}
		}
		return NOT_FINDED;
	}

	void vssd_inode::FindSelfSubForAll(std::wstring Inode, std::vector<vssd_inode*>& AllInode) const
	{
		int Result = 0;
		while (1)
		{
			Result = FindSelfSubForNext(Inode, Result);
			if (IsFinded(Result))
			{
				AllInode.push_back(SubInodes[Result]);
				Result++;
			}
			else {
				break;
			}
		}
		return;
	}


	//获取father之后，修改father内容
	vssd_inode *  vssd_inode::GetFather() const
	{
		return Father;
	}
	//修改father值
	void vssd_inode::SetFather(vssd_inode * aFather)
	{
		Father = aFather;
	}


	const std::vector<vssd_inode*>& vssd_inode::GetSubInodes()const
	{
		return SubInodes;
	}


	size_t vssd_inode::Serialize(std::vector<wchar_t>& Bytes)
	{
		size_t Start = Bytes.size();
		tool::string::PushString(GetName(), Bytes);
		tool::string::PushLengthValue(InodeTypeCode, Bytes);
		Content.Serialize(Bytes);
		tool::string::PushLengthValue((unsigned int)SubInodes.size(), Bytes);
		if (InodeTypeCode == IS_FOLDER) {
			for (size_t i = 0; i < SubInodes.size(); i++)
			{
				SubInodes.at(i)->Serialize(Bytes);
			}
		}
		return Start;
	}

	void vssd_inode::DeSerialize(std::vector<wchar_t>& ByteVssd, int& Pos)
	{
		SetName(tool::string::GetString(ByteVssd, Pos));
		InodeTypeCode = tool::string::GetLengthValue(ByteVssd, Pos);
		Content.DeSerialize(ByteVssd, Pos);
		int SubSize = tool::string::GetLengthValue(ByteVssd, Pos);

		if (InodeTypeCode == IS_FOLDER) {
			for (int i = 0; i < SubSize; i++)
			{
				vssd_inode *sub = new vssd_inode(L"", IS_FOLDER);
				LoadOneSub(sub);
				sub->DeSerialize(ByteVssd, Pos);
			}
		}


	}

	vssd_inode::~vssd_inode()
	{ 
		if (LinkPath)
			delete LinkPath;
	}

	void vssd_inode::Display()
	{
		std::wcout << L"<vssd_inode class>" << std::endl;
		std::wcout << L"\tName = " << Name.Get() << std::endl;
	}
	void vssd_inode::CopyFolder(const  VirtualDisk & a, vssd_inode * src)
	{
		if (IsFile()) {
			Content = *new vssd_content(src->Content);
		}
		else if (IsFolder()) {
			SubInodes.clear();
			for (size_t i = 0; i < src->SubSize(); i++)
			{
				vssd_inode * sub = new vssd_inode(src->SubInodes[i]->GetName(), src->SubInodes[i]->InodeTypeCode);

				sub->CopyFolder(a,src->SubInodes[i]);
			}
			return;
		}
		else if (IsLinkD()) {
			vssd_inode * sub = this;
			sub = vssd_optcmd::CheckLink(a, sub);
			if (sub) 
			{
				sub->SubInodes.clear();
				for (size_t i = 0; i < sub->SubSize(); i++)
				{
					vssd_inode * sub1 = new vssd_inode(sub->SubInodes[i]->GetName(), sub->SubInodes[i]->InodeTypeCode);

					sub1->CopyFolder(a, sub->SubInodes[i]);
				}
				return;
			}
			else
			{
				//链接地址不存在
			}
		}
		else if (IsLinkF()) {
			 
		}
		

	}
	void vssd_inode::AddContent(wchar_t Byte)		//追加字符
	{
		if (IsFile())
		{
			Content.Add(Byte);
		}
		else
		{
			std::cout << "Can not write to or read From a Inode or a Link" << std::endl;
		}
	}
	void vssd_inode::SetContentString(std::wstring str)		//追加字符
	{
		if (IsFile())
		{
			for (size_t i = 0; i < str.size(); i++)
			{
				Content.SetString(str);
			}
		}
		else
		{
			std::cout << "Can not write to or read From a Inode or a Link" << std::endl;
		}
	}
	void vssd_inode::PrintContent()			//返回NULL 和 下一个字符
	{

		if (IsFile())
		{
			Content.Print();
		}
		else
		{
			std::cout << "Can not write to or read From a Inode or a Link" << std::endl;
		}
	}
}