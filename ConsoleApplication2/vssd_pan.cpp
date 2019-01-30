#include "pch.h" 

sjh::vssd_Inode * sjh::vssd_pan::GetRoot()
{
	return root;
}

sjh::tool_path & sjh::vssd_pan::GetNowPath()
{
	return NowPath;
}

sjh::vssd_Inode * sjh::vssd_pan::GetNooowPos()
{
	return NowPath.GetNow();
}

void sjh::vssd_pan::PrintNowPathForCmd()
{ 
	PrintNowPath(); 
	std::cout << ">"; 
	
} 
void sjh::vssd_pan::PrintNowPath()
{
	std::wcout << NowPath.GetPathWstring(); 
}
int sjh::vssd_pan::Serialize(std::vector<wchar_t>& Byte_Toptable)
{
	int Start = Byte_Toptable.size();
	sjh::tools_vssd::PushString(root->GetName(), Byte_Toptable);
	NowPath.Serialize(Byte_Toptable); 
	return Start;
}
void sjh::vssd_pan::DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos)
{
	std::wstring panName = sjh::tools_vssd::GetString(ByteVssd,Pos);
	NowPath.DeSerialize(ByteVssd,Pos);
} 
sjh::vssd_pan::vssd_pan(sjh::vssd_Inode * aroot, sjh::vssd_Inode * aGenius)
{
	root = aroot; 
	NowPath.LoadOneSub(aroot); 
}

 
//根据目前目录位置和相对路径查找

 



sjh::vssd_pan::~vssd_pan()
{
}

void sjh::vssd_pan::Display()
{
}
