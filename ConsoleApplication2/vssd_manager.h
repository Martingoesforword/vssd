#pragma once
#include "pch.h"
#include "base_operater.h" 
#include "vssd_disk.h"
#include "vssd_optcmd.h"
namespace sjh {
	class vssd_manager
	{ 
		std::vector<base_operater*> operators;
		VirtualDisk* disk;  
	public:
		
		vssd_manager();  
		
		void CreateDiskDemo1(); 

		int ComeInOperaterByAccessWay(int OptType);
		
		static const int TYPE_CMD = 1;
		~vssd_manager();
	};
}
