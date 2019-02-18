#pragma once 
namespace sjh { 
	class VirtualDisk;
	class base_operater
	{ 
	public:
		int				OptType;
		virtual void	InitType() = 0;
		virtual int		ExeInterface(VirtualDisk & MyVssd) = 0; 
		base_operater():OptType() {}
	};
}
