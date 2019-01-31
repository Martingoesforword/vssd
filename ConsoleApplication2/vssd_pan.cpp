#include "vssd_pan.h"
namespace sjh { 
	vssd_inode * vssd_pan::GetRoot()
	{
		return root;
	}
 

	tools_path & vssd_pan::GetNowPath()
	{
		return NowPath;
	}

	vssd_inode * vssd_pan::GetNooowPos()
	{
		return NowPath.GetNow();
	}

	 
	std::wstring vssd_pan::GetNowPathWString()
	{ 
		return NowPath.GetPathWstring();
	}
	 
	int vssd_pan::Serialize(std::vector<wchar_t>& Byte_Toptable)
	{
		int Start = Byte_Toptable.size();
		tool::stringtools::PushString(root->GetName(), Byte_Toptable);
		NowPath.Serialize(Byte_Toptable);
		return Start;
	}
	void vssd_pan::DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos)
	{
		std::wstring panName = tool::stringtools::GetString(ByteVssd, Pos);
		NowPath.DeSerialize(ByteVssd, Pos);
	}
	vssd_pan::vssd_pan(vssd_inode * aroot, vssd_inode * aGenius)
	{
		root = aroot;
		NowPath.LoadOneSub(aroot);
	}


	//根据目前目录位置和相对路径查找
	 


	vssd_pan::~vssd_pan()
	{
	}

	void vssd_pan::Display()
	{
	}
}