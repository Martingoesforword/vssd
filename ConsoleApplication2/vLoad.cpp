#include "pch.h" 
void sjh::tool_vcmd::vLoad(vssd & MyVssd, std::wstring & GetFrom)
{
	MyVssd.Serial.clear();
	char ch;
	std::ifstream Vssdfile(GetFrom, std::ios::binary);
	if (!Vssdfile.is_open())
	{
		std::cout << "Error opening file"; exit(1);
	}
	while (!Vssdfile.eof())
	{
		ch = ' ';



		for (size_t i = 0; i < 36; i++)
		{
			Vssdfile.read(&ch, 1);
			MyVssd.Serial.push_back(ch);
		}
		unsigned int Bytelength = 0;
		vssd_tool::Get4BUint(MyVssd.Serial, 32, Bytelength);

		for (size_t i = 0; i < Bytelength - 36; i++)
		{
			Vssdfile.read(&ch, 1);
			MyVssd.Serial.push_back(ch);
		}

		Vssdfile.close();


	}
	//��ȡ�ļ�ָ��
	//FILE *file;
	//MyVssd.GetFromRealfile(file);
	MyVssd.DeSerialize(MyVssd.Serial);
	MyVssd.Serial.clear();
}
