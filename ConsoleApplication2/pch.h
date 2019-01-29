#pragma once  
#define FILEMAXSIZE 100
#include <string>
#include <iostream> 
#include <vector>  
#include <fstream> 
#include <windows.h>
#include <iomanip>
#include "conio.h"
namespace sjh {
	class base_contentable;
	class base_serializable;
	class base_progress;
	class base_namedable;
	class base_displayable;
	class vssd_folder;
	class vssd_pan;
	class tool_path; 
	class vssd_disk;
	class vcmd; 
	class tools_vssd;
	class vssdDel;
	class vssdCat;
	class vssdCd;
	class vssdCls;
	class vssdCopy;
	class vssdDir;
	class vssdLoad;
	class vssdMkdir;
	class vssdMklink;
	class vssdMove;
	class vssdRd;
	class vssdRen;
	class vssdSave;

	#include "base_contentable.h"
	#include "base_serializable.h"
	#include "base_displayable.h" 
	#include "base_progress.h" 
	#include "base_namedable.h"
	#include "vssd_vcmd.h"  
	#include "vssd_path.h"				//sjh::tool_path在下面类中的属性里以实例存在，需要提前写 
	#include "vssd_pan.h"			  
	#include "vssd_folder.h"  
	#include "vssd_disk.h" 
	#include "tools_vssd.h"
	#include "vssdDel.h"
	#include "vssdCat.h"
	#include "vssdCd.h"
	#include "vssdCls.h"
	#include "vssdCopy.h"
	#include "vssdDir.h"
	#include "vssdLoad.h"
	#include "vssdMkdir.h"
	#include "vssdMklink.h"
	#include "vssdMove.h"
	#include "vssdRd.h"
	#include "vssdRen.h"
	#include "vssdSave.h"
	
	
}





/*



*/
