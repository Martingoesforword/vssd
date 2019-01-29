#include "pch.h" 
void sjh::vssdSave::vSave(vssd_disk & MyVssd, std::wstring & JumpTo)
{ 
	std::vector<wchar_t> Serial;
	MyVssd.Serialize(Serial);

	MyVssd.PutToRealFile(JumpTo, Serial);
	Serial.clear();
}
