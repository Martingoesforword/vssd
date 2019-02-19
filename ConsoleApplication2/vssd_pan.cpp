#include "pch.h"  
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

	void vssd_pan::SetNowPath(tools_path path)
	{
		NowPath = path;
	}

	vssd_inode * vssd_pan::GetNooowPos() const
	{
		return (vssd_inode *)NowPath.GetNowPtr();
	}
	 
	std::wstring vssd_pan::GetNowPathWString() const
	{ 
		return NowPath.GetPathWstring();
	}

	void vssd_pan::DeleteOneSub() 
	{
		NowPath.DeleteOneSub();
	}
	 
	size_t vssd_pan::Serialize(std::vector<wchar_t>& Byte_Toptable)
	{
		size_t Start = Byte_Toptable.size();
		tool::string::PushString(root->GetName(), Byte_Toptable);
		NowPath.Serialize(Byte_Toptable);
		return Start;
	}
	void vssd_pan::DeSerialize(std::vector<wchar_t>& ByteVssd, int & Pos)
	{
		std::wstring panName = tool::string::GetString(ByteVssd, Pos);
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
			<< " ������ C �еľ��� " << tool::string::WStringToString(root->GetName())
			<< "��\n ������к��� " << std::setfill('0') << std::setw(4) << std::setiosflags(std::ios::uppercase) << std::hex << reinterpret_cast<int>(root) / 0x10000
			<< " - " << std::setfill('0') << std::setw(4) << std::hex << std::setiosflags(std::ios::uppercase) << reinterpret_cast<int>(root) % 0x10000
			<< "\n";
	}

	vssd_pan::~vssd_pan()
	{
	}

	void vssd_pan::Display()
	{
	}
}