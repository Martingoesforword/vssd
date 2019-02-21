#include "pch.h"
#include "vssdCls.h"
namespace sjh {
	void vssdCls::vCls()
	{
		system("cls");
	}
	int vssdCls::Execute(VirtualDisk & MyVssd, const std::vector<std::wstring>& Rear)
	{
		vCls();
		return EXE_OK;
	}
}