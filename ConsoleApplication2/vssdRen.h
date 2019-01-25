#include "pch.h" 
class vssdRen {
public:
	static void vRen(vssd_disk & MyVssd, std::wstring & renCommand);
	static void vRen(vssd_disk & MyVssd, std::wstring & SrcCommand, std::wstring & DesName);
};
//改名--目前路径
