#include "pch.h"
#include "vssd_content.h"
namespace sjh{
	void vssd_content::Add(wchar_t Byte)		//׷���ַ�
	{ 
		Content.push_back(Byte); 
		FreshTime();
	}
	void vssd_content::SetString(std::wstring str)		//׷���ַ�
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			Content.push_back(*((unsigned char*)&str[i] + 0));
			Content.push_back(*((unsigned char*)&str[i] + 1));
		} 

	}
	void vssd_content::Print()			//����NULL �� ��һ���ַ�
	{
		for (size_t i = 0; i < Content.size(); i++)
		{
			std::cout << Content[i];
		}
		std::cout << std::endl; 
	}
	size_t vssd_content::Size()
	{
		return Content.size();
	}

	std::time_t vssd_content::GetTime() const
	{
		return Time.Get();
	}

	void vssd_content::FreshTime()
	{
		Time.Fresh();
	}

}
