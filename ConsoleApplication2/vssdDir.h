#include "pch.h" 
class vssdDir 
{
public: 
	static void vDir(sjh::vssd_disk & MyVssd, int Type); 
	static void vDir(sjh::vssd_disk & MyVssd, std::vector<std::wstring> Dirs, int Type);
	static void vDir(sjh::vssd_disk & MyVssd, std::wstring & DirCommand);

};
