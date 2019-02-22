#include "pch.h"
#include "vssd_content.h"
#include "tools_vssd.h"
namespace sjh{
	size_t vssd_content::Serialize(std::vector<wchar_t>& Byte)
	{
		size_t a = Byte.size();
		tool::string::PushWcharVector(Content, Byte); 
		tool::string::PushTime(GetTime(), Byte);
		return a;
	}
	void vssd_content::DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos)
	{
		tool::string::GetWcharVector(Content, ByteVssd, Pos); 
		std::time_t	 aTime;
		tool::string::GetTime(ByteVssd, aTime, Pos);
		Time.Set(aTime);
	}
	void vssd_content::Add(wchar_t Byte)		//追加字符
	{ 
		Content.push_back(Byte); 
		FreshTime();
	}
	void vssd_content::SetString(std::wstring str)		//追加字符
	{
		for (size_t i = 0; i < str.size(); i++)
		{
			Content.push_back(*((unsigned char*)&str[i] + 0));
			Content.push_back(*((unsigned char*)&str[i] + 1));
		} 

	}
	void vssd_content::Print()			//返回NULL 和 下一个字符
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

	void vssd_content::SetTime(std::time_t a)
	{
		Time.Set(a);
	}

	void vssd_content::FreshTime()
	{
		Time.Fresh();
	}

}
