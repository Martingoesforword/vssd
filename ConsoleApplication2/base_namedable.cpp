#include "pch.h"
#include "base_namedable.h"
namespace sjh {
	 
	std::wstring base_namedable::GetName()
	{
		return Name;
	}

	void base_namedable::SetName(std::wstring aName)
	{
		Name = aName;
	}

	base_namedable::base_namedable(std::wstring aName)
	{
		Name = aName;
	}



	base_namedable::~base_namedable()
	{
	}
}
 