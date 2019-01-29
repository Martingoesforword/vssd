 #include "pch.h" 

int main()
{ 
	sjh::vssd_disk *MyVssd = sjh::vssd_disk::CreatVssd();  
	//初始化vssd
	 
	
	while (1)
	{ 
		//输出盘内路径并等待输入
		MyVssd->GetNowTop()->ShowNowPosForCmd(); 
		//获取字符串并使用工具函数转化输入字符串为wstring型
		std::string Command;
		std::getline(std::cin,Command); 
		std::wstring LCommand = sjh::tools_vssd::StringToWString(Command); 
		//跳入vcmd
		sjh::vssd_vcmd::v_cmd_comein(*MyVssd, LCommand);
		std::cout << "\n";

	}
	 
}
 