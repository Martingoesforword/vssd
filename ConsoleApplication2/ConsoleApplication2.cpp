// ConsoleApplication2.cpp : 此文件包含 L"main" 函数。程序执行将在此处开始并结束。
//
 
#include "pch.h" 
 
int main()
{
	 
	
    std::cout << "Hello! My Name is VirtualSSD, Now you will Type Command for My work\n"; 
	std::string Command;
	/**
	std::cin >> Command;
	Vssd_path p1(Command,1);
	p1.testprint();
	*/

	sjh::vssd_folder Genius(L"",1); 
	
	sjh::vssd_folder c_pan(L"c:",1);//新建根目录
	sjh::vssd_foldertop MyTopcpan(&c_pan, &Genius);//加载根目录
	sjh::vssd MyVssd(&MyTopcpan, &Genius,L"firstVssd");
	MyVssd.LinkTop(&MyTopcpan);
	

	sjh::vssd_folder sjhc(L"sjh",1);
	sjh::vssd_folder f1c(L"src",1);
	sjh::vssd_folder f2c(L"app",1);
	sjh::vssd_folder f3c(L"src",1);
	sjh::vssd_folder f4c(L"app",1);

	sjh::vssd_foldertop *MyTop = MyVssd.GetNowTop();
	sjh::vssd_folder * Now = MyTop->root;

	Now->VssdFolderLink(&sjhc);
	Now->VssdFolderLink(&f1c);
	Now->VssdFolderLink(&f2c);
	f2c.VssdFolderLink(&f3c);
	f2c.VssdFolderLink(&f4c); 
	
	//创建卷2:d盘
	sjh::vssd_folder d_pan(L"d:",1);//新建根目录
	sjh::vssd_foldertop MyTopdpan(&d_pan, &Genius);//加载根目录
	MyVssd.LinkTop(&MyTopdpan);
	sjh::vssd_folder sjhd(L"sjh2",1);
	sjh::vssd_folder songtxt(L"song.txt", 0); 
	songtxt.SetContentString(L"sjh sjh sjh fdkjshngfjdgjfgjfjgkfjgkjf  sjh sjh sjh");
	sjh::vssd_folder f1d(L"src2",1);
	sjh::vssd_folder f2d(L"app2",1);
	sjh::vssd_folder f3d(L"src2",1);
	sjh::vssd_folder f4d(L"app2",1); 
	sjh::vssd_folder * Nowd = MyTopdpan.root; 
	Nowd->VssdFolderLink(&sjhd);
	Nowd->VssdFolderLink(&f1d);
	Nowd->VssdFolderLink(&f2d);
	Nowd->VssdFolderLink(&songtxt);
	f2d.VssdFolderLink(&f3d);
	f2d.VssdFolderLink(&f4d);  
	/*std::wcout << "目前磁盘无文件，文件夹有：\n c:\\sjh c:\\Src c:\\app c:\\app\\Src c:\\app\\app \n d:\\sjh2 d:\\Src2 d:\\app2 d:\\app2\\Src2 d:\\app2\\app2" << std::endl;
	std::wcout << "目前实现命令：cd [磁盘:][..][.][无..和.的相对路径]\n 例如:cd app/sjh"<<std::endl;
	std::wcout << "\t命令：cls 命令：dir " << std::endl;*/

	Genius.VssdFolderLink(&d_pan);
	Genius.VssdFolderLink(&c_pan);  
	//向虚拟根目录添加盘 
	

	char ch = 'x';
	char prech = 'x';
	int index = 0;
	size_t foldernamelength = 0;
	while(1){
		
		foldernamelength = 0;
		MyTop = MyVssd.GetNowTop();
		MyTop->ShowNowPosForCmd();
		Command.clear();
		bool flag = 0;
		while (1) {
			if(ch) prech = ch;
			if (!flag) { ch = _getch(); flag = 1; }
			
			if (ch == '\t' && prech == ' ') {
				aaa:
				if (index < MyVssd.GetNowTop()->GetNowPos()->SubFolders.size()) {
					std::wstring foldername;
					foldername = MyVssd.GetNowTop()->GetNowPos()->SubFolders[index]->GetName();
					std::cout << sjh::vssd_tool::WStringToString(foldername);
					Command.append(sjh::vssd_tool::WStringToString(foldername));
					foldernamelength = foldername.size();
					prech = 'x';
					index++;
				}
				else {
					index = 0;
					if (index < MyVssd.GetNowTop()->GetNowPos()->SubFolders.size()) {
						std::wstring foldername;
						foldername = MyVssd.GetNowTop()->GetNowPos()->SubFolders[index]->GetName();
						std::cout << sjh::vssd_tool::WStringToString(foldername);
						Command.append(sjh::vssd_tool::WStringToString(foldername));
						foldernamelength = foldername.size();
						prech = 'x';
					}
				}
				
			}
		else if (ch == '\t') {
				if (Command.size()) {
					for (size_t i = 0; i < foldernamelength; i++)
					{
						Command.pop_back();
						putchar('\b');
						putchar(' ');
						putchar('\b');
						
					}
					
					goto aaa;
				}

			}
			else if (ch == '\b') { 
				if (Command.size()) {
					Command.pop_back();
					putchar('\b');
					putchar(' ');
					putchar('\b');
				}
				
			}
			else if (ch == '\b') {
				puts("\b \b");
			}
			else if (ch == '\r') {
				break;
			}
			else {
				if (ch) {
					putchar(ch);
					Command.push_back(ch);
				}
			}
			flag = 0;

		}
		puts("\n");
		std::wstring LCommand = sjh::vssd_tool::StringToWString(Command);

		sjh::tool_vcmd::v_cmd_comein(MyVssd, LCommand);




		

	}

	//获得命令Command（命令）的首字符串Code
	//对比Code进入选项
	//若为dir，则分析之后的Command并将之后的转化为路径（对象）

}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
