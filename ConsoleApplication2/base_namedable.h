#pragma once  
#include "pch.h"  
namespace sjh {
	class base_namedable
	{
	protected:
		std::wstring Name;
	public:
		//ԭʼ����
		base_namedable(std::wstring aName) :Name(NAME_INIT) {}

		//name���
		void				SetName(std::wstring aName);
		const std::wstring&	GetName() const;
		static const std::wstring NAME_INIT;
	};
	const std::wstring base_namedable::NAME_INIT = L"[SJH]";
}