#include "pch.h"
#include "vssdSave.h"
namespace sjh {
	void vssdSave::vSave(vssd_manager & MyVssd, std::wstring & JumpTo)
	{
		std::vector<wchar_t> Serial;
		MyVssd.Serialize(Serial);

		tool::stringtools::PushToRealFile(JumpTo, Serial);
		Serial.clear();
	}

	int vssdSave::Execute(vssd_manager & MyVssd, std::vector<std::wstring> Rear)
	{
		return EXE_OK;
	}
	 
}