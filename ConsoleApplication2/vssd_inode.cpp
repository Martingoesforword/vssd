#include "pch.h"  
#include "vssd_inode.h"

namespace sjh {

	const std::wstring vssd_inode::VssdTypeName[3] = { L"FILE",L"DIR", L"SYMLINKD" };


	std::wstring vssd_inode::GetTypeName() const
	{
		return VssdTypeName[InodeTypeCode];
	}

	vssd_inode::vssd_inode(std::wstring aName, int aCode) :Name(vssd_name(aName)), InodeTypeCode(aCode)
	{ 
	}


	void vssd_inode::LoadOneSub(vssd_inode *LinktoSub)
	{
		LinktoSub->SetFather(this);
		SubInodes.push_back(LinktoSub);

	}




	void vssd_inode::PrintHead(std::wstring now) const
	{
		std::cout
			<< "\n " << tool::stringtools::WStringToString(now) << " 的目录\n"
			<< std::endl;
		
	}
	void vssd_inode::PrintOTP() const
	{
		std::cout
			<< tool::stringtools::WStringToString(tool::stringtools::GetTimeWString(Content.GetTime()))
			<< "    "
			<< std::setiosflags(std::ios::right)
			<< "<" << tool::stringtools::WStringToString(GetTypeName()) << ">"
			<< std::setfill(' ') << std::setw(10) << " "
			<< "."
			<< std::endl;
		std::cout
			<< tool::stringtools::WStringToString(tool::stringtools::GetTimeWString(GetFather()->Content.GetTime()))
			<< "    "
			<< std::setiosflags(std::ios::right)
			<< "<" << tool::stringtools::WStringToString(GetFather()->GetTypeName()) << ">"
			<< std::setfill(' ')
			<< std::setw(10)
			<< " "
			<< ".."
			<< std::endl;
		
	}
	void vssd_inode::PrintFileInfo()
	{
		std::cout
			<< tool::stringtools::GetTimeString(Content.GetTime())
			<< "    "
			<< std::setfill(' ') << std::setw(14) << tool::stringtools::GetSizeString((unsigned int)Content.Size() * sizeof(unsigned char))
			<< " " << tool::stringtools::WStringToString(GetName())
			<< std::endl;
	}
	void vssd_inode::PrintFoLiInfo()
	{
		std::cout
			<< tool::stringtools::GetTimeString(Content.GetTime()) << "    "
			<< std::setiosflags(std::ios::right)
			<< "<" << tool::stringtools::WStringToString(GetTypeName()) << ">"
			<< std::setfill(' ') << std::setw(10) << " "
			<< tool::stringtools::WStringToString(GetName())
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
	
	void vssd_inode::PrintAllSub( int pram, std::wstring now) const
	{ 
		  
		PrintHead(now);
		PrintOTP();  

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
				if (SubInodes[i]->IsFile())
				{
					PrintHead(now); 
					SubInodes[i]->PrintFileInfo();
				}
				else
				{
					std::wstring a = now;
					a.append(L"\\");
					a.append(SubInodes[i]->GetName());
					

					SubInodes[i]->PrintAllSub(pram, a);
				}
				
			}
		}

	}

	void vssd_inode::DeleteOneSub(vssd_inode * deletInode)
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

			if (SubInodes.at(j)->GetName().compare(deletInode->GetName()) == sjh::IS_SAMESTRING)
			{
				SubInodes.at(j)->DeleteWholeTree();
				SubInodes.at(j)->~vssd_inode();
				std::vector<vssd_inode *>::iterator it = SubInodes.begin();

				SubInodes.erase(it + j);
				return;
			}
			else
			{
				j++;
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

			if (SubInodes.at(j)->GetName().compare(deletInode->GetName()) == sjh::IS_SAMESTRING)
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





	size_t vssd_inode::FindSelfSubForNext(std::wstring& Inode, size_t StartIndex) const
	{
		for (size_t i = StartIndex; i < SubInodes.size(); i++)
		{
			if (SubInodes.at(i) != NULL)
			{
				if (tool::stringtools::WStringMatch(SubInodes.at(i)->GetName(), Inode) != 0)
				{
					return i;
				}
				if (i > SubInodes.size())
				{
					break;
				}
			}
		}
		return (size_t)NOT_FINDED;
	}

	void vssd_inode::FindSelfSubForAll(std::wstring Inode, std::vector<vssd_inode*>& AllInode)
	{
		size_t Result = 0;
		//循环体内语句控制循环的进行，非线性控制
		while (1)
		{
			Result = FindSelfSubForNext(Inode, Result);
			if (Result != NOT_FINDED)
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

	vssd_inode * vssd_inode::FindFolderByLink() const
	{
		const vssd_inode *Inode = this;
		while (Inode->IsLink())
		{
			Inode = Inode->SubInodes[0];
		}
		return (vssd_inode *)Inode;
	}




	const vssd_inode *  vssd_inode::GetFather() const
	{
		return Father;
	}
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
		tool::stringtools::PushString(GetName(), Bytes);
		tool::stringtools::PushLengthValue(InodeTypeCode, Bytes);
		//tool::stringtools::PushWcharVector(Content, Bytes);
		tool::stringtools::PushLengthValue((unsigned int)SubInodes.size(), Bytes);
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
		SetName(tool::stringtools::GetString(ByteVssd, Pos));
		InodeTypeCode = tool::stringtools::GetLengthValue(ByteVssd, Pos);
		//tool::stringtools::GetWcharVector(Content, ByteVssd, Pos);
		int SubSize = tool::stringtools::GetLengthValue(ByteVssd, Pos);

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
		for (size_t i = 0; i < SubInodes.size(); i++)
		{
			delete SubInodes[i];
		}
	}

	void vssd_inode::Display()
	{
		std::wcout << L"<vssd_inode class>" << std::endl;
		std::wcout << L"\tName = " << Name.Get() << std::endl;
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
			for (size_t i = 0; i < str.length(); i++)
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