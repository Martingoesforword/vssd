#include "pch.h" 
void sjh::vssdSave::vSave(vssd_disk & MyVssd, std::wstring & JumpTo)
{ 
	MyVssd.Serialize(MyVssd.Serial);
	MyVssd.PutToRealFile(JumpTo); 
}
