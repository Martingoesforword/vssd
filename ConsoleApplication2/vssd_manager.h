#pragma once
#include "pch.h"
#include "vssd_disk.h"
namespace sjh {
	class vssd_manager
	{
		vssd_vcmd Vcmd; 
	public:
		vssd_manager();
		vssd_vcmd * GetVcmd();
		~vssd_manager();

		vssd_disk* disk;
		void CreateDisk(); 

		void ComeInVcmd();
		
		
	};
}
