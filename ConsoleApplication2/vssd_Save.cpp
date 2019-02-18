#include "pch.h"
#include "vssdSave.h"
namespace sjh {
	void vssdSave::vSave(VirtualDisk & MyVssd, std::wstring & JumpTo)
	{
		std::vector<wchar_t> Serial;
		MyVssd.Serialize(Serial);

		tool::stringtools::PushToRealFile(JumpTo, Serial);
		Serial.clear();
	}

	int vssdSave::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		return EXE_OK;
	}
	 
}