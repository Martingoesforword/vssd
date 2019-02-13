#include "vssd_inode.h"

namespace sjh {

	const std::wstring vssd_inode::VssdTypeName[3] = { L"FILE",L"DIR", L"SYMLINKD" };


	std::wstring vssd_inode::GetTypeName()
	{
		return VssdTypeName[InodeTypeCode];
	}

	vssd_inode::vssd_inode(std::wstring aName, int aCode) :base_namedable(aName)
	{
		InodeTypeCode = aCode;
	}


	void vssd_inode::LoadOneSub(vssd_inode *LinktoSub)
	{
		LinktoSub->SetFather(this);
		SubInodes.push_back(LinktoSub);

	}







	void vssd_inode::PrintAllSub( int pram, std::wstring now)//pram 1：tree  2：自己
	{
		using namespace sjh;  

		int p = 0;

		std::cout
			<< "\n " << tool::stringtools::WStringToString(now) << " 的目录\n"
			<< std::endl;
		std::cout
			<< tool::stringtools::WStringToString(tool::stringtools::GetTimeWString(GetCreateTime()))
			<< "    "
			<< std::setiosflags(std::ios::right)
			<< "<" << tool::stringtools::WStringToString(GetTypeName()) << ">"
			<< std::setfill(' ') << std::setw(10) << " "
			<< "."
			<< std::endl;
		std::cout
			<< tool::stringtools::WStringToString(tool::stringtools::GetTimeWString(GetFather()->GetCreateTime()))
			<< "    "
			<< std::setiosflags(std::ios::right)
			<< "<" << tool::stringtools::WStringToString(GetFather()->GetTypeName()) << ">"
			<< std::setfill(' ')
			<< std::setw(10)
			<< " "
			<< ".."
			<< std::endl;


		for (size_t i = 0; i < SubInodes.size(); i++)
		{


		defeatInode:

			if (SubInodes.at(p) != NULL)
			{
				if (SubInodes.at(p)->IsFile())
				{
					std::cout
						<< tool::stringtools::GetTimeString(SubInodes.at(p)->GetCreateTime())
						<< "    "
						<< std::setfill(' ') << std::setw(14) << tool::stringtools::GetSizeString((unsigned int)SubInodes[p]->GetContent().size() * sizeof(unsigned char))
						<< " " << tool::stringtools::WStringToString(SubInodes.at(p)->GetName())
						<< std::endl;
				}
				else {
					std::cout
						<< tool::stringtools::GetTimeString(SubInodes.at(p)->GetCreateTime()) << "    "
						<< std::setiosflags(std::ios::right)
						<< "<" << tool::stringtools::WStringToString(SubInodes[p]->GetTypeName()) << ">"
						<< std::setfill(' ') << std::setw(10) << " "
						<< tool::stringtools::WStringToString(SubInodes.at(p)->GetName())
						<< std::endl;
				}
			}
			else
			{
				p++; goto defeatInode;
			}
			p++;
		}
		if (pram == 1) {
			for (size_t i = 0; i < SubInodes.size(); i++)
			{
				now.append(GetName());
				now.append(L"\\");
				SubInodes[i]->PrintAllSub(pram, now);
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

			if (SubInodes.at(j)->GetName().compare(deletInode->GetName()) == IS_SAMESTRING)
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

			if (SubInodes.at(j)->GetName().compare(deletInode->GetName()) == IS_SAMESTRING)
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





	size_t vssd_inode::FindSelfSubForFirst(std::wstring Inode, size_t StartIndex)
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
			Result = FindSelfSubForFirst(Inode, Result);
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

	vssd_inode * vssd_inode::FindFolderByLink()
	{
		vssd_inode *Inode = this;
		while (Inode->IsLink())
		{
			Inode = Inode->SubInodes[0];
		}
		return Inode;
	}




	vssd_inode *  vssd_inode::GetFather()
	{
		return Father;
	}
	void vssd_inode::SetFather(vssd_inode * aFather)
	{
		Father = aFather;
	}

	void vssd_inode::AddContent(wchar_t Byte)		//追加字符
	{
		if (IsFile())
		{
			GetContent().push_back(Byte);
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
				GetContent().push_back(*((unsigned char*)&str[i] + 0));
				GetContent().push_back(*((unsigned char*)&str[i] + 1));
			}

		}
		else
		{
			std::cout << "Can not write to or read From a Inode or a Link" << std::endl;
		}
	}
	std::vector<vssd_inode*>& vssd_inode::GetSubInodes()
	{
		return SubInodes;
	}
	void vssd_inode::PrintContent()			//返回NULL 和 下一个字符
	{
		static int index = -1;
		if (IsFile())
		{
			for (size_t i = 0; i < GetContent().size(); i++)
			{
				std::cout << GetContent()[i];
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Can not write to or read From a Inode or a Link" << std::endl;
		}
	}

	size_t vssd_inode::Serialize(std::vector<wchar_t>& Bytes)
	{
		size_t Start = Bytes.size();
		tool::stringtools::PushString(GetName(), Bytes);
		tool::stringtools::PushLengthValue(InodeTypeCode, Bytes);
		tool::stringtools::PushWcharVector(GetContent(), Bytes);
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
		tool::stringtools::GetWcharVector(GetContent(), ByteVssd, Pos);
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
	}

	void vssd_inode::Display()
	{
		std::wcout << L"<vssd_inode class>" << std::endl;
		std::wcout << L"\tName = " << Name << std::endl;
	}

}