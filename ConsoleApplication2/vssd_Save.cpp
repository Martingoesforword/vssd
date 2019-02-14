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

	void vssdSave::Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear)
	{
		status = EXE_OK;
	}
	 
}