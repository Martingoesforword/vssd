#include "pch.h"
#include "vssdSave.h"
namespace sjh {
	
	void vssdSave::vSave(VirtualDisk & MyVssd, const std::wstring & JumpTo)
	{
		std::vector<wchar_t> Serial; 
		MyVssd.Serialize(Serial);

		tool::string::PushToRealFile(JumpTo, Serial);
		Serial.clear();
	}

	int vssdSave::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		vSave(MyVssd, Rear[1]);
		return EXE_OK;
	}
	 
}