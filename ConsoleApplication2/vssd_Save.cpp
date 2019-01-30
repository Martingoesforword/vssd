#include "pch.h" 
void sjh::vssdSave::vSave(vssd_disk & MyVssd, std::wstring & JumpTo)
{ 
	std::vector<wchar_t> Serial;
	MyVssd.Serialize(Serial);

	tools_vssd::PushToRealFile(JumpTo, Serial);
	Serial.Clear();
}
