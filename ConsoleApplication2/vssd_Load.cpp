#include "pch.h" 
void sjh::vssdLoad::vLoad(vssd_disk & MyVssd, std::wstring & GetFrom)
{
	std::vector<wchar_t> aSerial; 
	tools_vssd::GetFromRealfile(GetFrom, aSerial); 
	int Pos = 0;
	MyVssd.DeSerialize(aSerial, Pos);
	aSerial.clear();
}
