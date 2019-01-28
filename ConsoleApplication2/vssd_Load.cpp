#include "pch.h" 
void sjh::vssdLoad::vLoad(vssd_disk & MyVssd, std::wstring & GetFrom)
{
	 
	MyVssd.Serial.clear();
	MyVssd.GetFromRealfile(GetFrom);
	
	MyVssd.DeSerialize(MyVssd.Serial); 
}
