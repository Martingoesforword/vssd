#include "pch.h"
#include "vssdLoad.h"

namespace sjh {
	void vssdLoad::vLoad(VirtualDisk & MyVssd, std::wstring & GetFrom)
	{
		std::vector<wchar_t> aSerial;
		tool::stringtools::GetFromRealfile(GetFrom, aSerial);
		int Pos = EXE_OK;
		MyVssd.DeSerialize(aSerial, Pos);
		aSerial.clear();
	}
	int vssdLoad::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		return EXE_OK;
	}
}