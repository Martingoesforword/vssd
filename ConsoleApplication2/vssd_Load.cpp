#include "pch.h"
#include "vssdLoad.h"

namespace sjh {
	void vssdLoad::vLoad(vssd_disk & MyVssd, std::wstring & GetFrom)
	{
		std::vector<wchar_t> aSerial;
		tool::stringtools::GetFromRealfile(GetFrom, aSerial);
		int Pos = EXE_OK;
		MyVssd.DeSerialize(aSerial, Pos);
		aSerial.clear();
	}
	int vssdLoad::Execute(vssd_disk & MyVssd, std::vector<std::wstring> Rear)
	{
		return EXE_OK;
	}
}