#pragma once  
namespace sjh {
	class base_progress
	{
	private:
		int status;
	public:
		virtual int excute() = 0; 
	};

}