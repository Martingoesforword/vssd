#pragma once  
namespace sjh {
	class base_displayable
	{
	public:
		virtual void Display() = 0;
		base_displayable();
		~base_displayable();
	};

}