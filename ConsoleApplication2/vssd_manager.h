#pragma once
#include "pch.h"
#include "base_operater.h" 
#include "vssd_disk.h"
#include "vssd_optcmd.h"
namespace sjh {
	class vssd_manager
	{ 
	private:
		std::vector<base_operater*>		operators;
		VirtualDisk*	disk;  
	public: 
		//原始构造
		vssd_manager();
		~vssd_manager();

		//Demo1相关
		void CreateDiskDemo1(); 

		//operators相关
		static const int TYPE_CMD = 1;
		int ComeInOperaterByAccessWay(int OptType); 
	};
}
