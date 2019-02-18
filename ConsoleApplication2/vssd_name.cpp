#include "pch.h"
#include "vssd_name.h"
namespace sjh {
	 
	const std::wstring& vssd_name::Get() const
	{
		return Name;
	}

	void vssd_name::Set(std::wstring aName)
	{
		Name = aName;
	} 
	 
	vssd_name::vssd_name()
	{
	}

	vssd_name::vssd_name(std::wstring aName) :Name(aName)
	{ 
	}  
}
 