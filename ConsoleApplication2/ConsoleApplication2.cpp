#include "pch.h"  
#include "all.h"
#include "test.h" 
using namespace sjh; 
int TESTT = 0;
int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetBreakAlloc(258);
	if (TESTT) { 
		std::vector<int> *aa = 0;
		int a = test<int>(1)(2);
		new(aa) std::vector<int>();
		//new(1);
		//atlalloc()
	}
	else {

		vssd_manager manager;
		manager.CreateDiskDemo1();
		manager.ComeInOperaterByAccessWay(manager.TYPE_CMD); 
	}
	
}
