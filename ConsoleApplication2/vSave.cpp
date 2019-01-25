#include "pch.h" 
void sjh::vssdSave::vSave(vssd_disk & MyVssd, std::wstring & JumpTo)
{

	MyVssd.Serialize(MyVssd.Serial);

	std::ofstream Vssdfile(JumpTo, std::ios::binary);
	if (Vssdfile.is_open())
	{
		std::wstring data;
		tools_vssd::GetStringAnd0(MyVssd.Serial, 0, MyVssd.Serial.size(), data);

		Vssdfile.write((const char*)&data[0], data.size());

		Vssdfile.close();
		MyVssd.Serial.clear();
	}
	else {
		std::cout << "Error opening file";
	}


	//获取文件指针
	//FILE *file= nullptr;  
	//MyVssd.puttoRealfile(file);
}
