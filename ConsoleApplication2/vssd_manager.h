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
		//ԭʼ����
		vssd_manager();
		~vssd_manager();

		//Demo1���
		void CreateDiskDemo1(); 

		//operators���
		static const int TYPE_CMD = 1;
		int ComeInOperaterByAccessWay(int OptType); 
	};
}
