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
	 
	size_t vssd_pan::Serialize(std::vector<wchar_t>& Byte_Toptable)
	{
		size_t Start = Byte_Toptable.size();
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


	//����ĿǰĿ¼λ�ú����·������
	 
	void vssd_pan::PrintPanInfo() {
		using namespace sjh;
		std::cout
			<< " ������ C �еľ��� " << tool::stringtools::WStringToString(root->GetName())
			<< "��\n ������к��� " << std::setfill('0') << std::setw(4) << std::setiosflags(std::ios::uppercase) << std::hex << (int)(void*)(root) / 0x10000
			<< " - " << std::setfill('0') << std::setw(4) << std::hex << std::setiosflags(std::ios::uppercase) << (int)(void*)(root) % 0x10000
			<< "\n";
	}

	vssd_pan::~vssd_pan()
	{
	}

	void vssd_pan::Display()
	{
	}
}