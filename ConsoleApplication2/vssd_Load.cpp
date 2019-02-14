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
	void vssdLoad::Execute(VirtualDisk & MyVssd, std::vector<std::wstring>& Rear)
	{
		status = EXE_OK;
	}
}