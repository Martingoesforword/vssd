#include "pch.h"  
#include "all.h"
#include "test.h" 
using namespace sjh; 
int TESTT = 0;
int main()
{
	
	if (TESTT) { 

		std::vector<vssd_manager> aa;
		vssd_manager a;
		aa.push_back(a);
		//int a = test<int>(1)(2);
		//new(aa) std::vector<int>();
		//new(1);
		//atlalloc()
	}
	else {
		 
		vssd_manager manager;
		manager.CreateDiskDemo1();
		manager.ComeInOperaterByAccessWay(manager.TYPE_CMD); 
	}
	
}
