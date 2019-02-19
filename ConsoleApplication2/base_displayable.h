#pragma once  
namespace sjh {
	class base_displayable
	{
	public:
		virtual ~base_displayable() {};
		virtual void	Display() = 0; 
	};

}