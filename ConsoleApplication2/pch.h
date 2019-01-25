#pragma once  
#define FILEMAXSIZE 100
#include <string>
#include <iostream> 
#include <vector>  
#include <fstream> 
#include <windows.h>
#include "conio.h"
namespace sjh {

	class vssd_folder;
	class vssd_pan;
	class tool_path; 
	class vssd_disk;
	class vcmd; 
	class vssd_tool;

	#include "vssd_vcmd.h" 
	
	#include "vssd_path.h"				//sjh::tool_path在下面类中的属性里以实例存在，需要提前写 
	#include "vssd_pan.h"			  
	#include "vssd_folder.h"  
	#include "vssd_disk.h" 
	#include "tools_vssd.h"
}





/*



*/
