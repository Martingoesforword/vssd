// ConsoleApplication2.cpp : 此文件包含 L"main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h" 

int main()
{


	 
	std::string Command; 
	sjh::vssd_disk *MyVssd = sjh::vssd_disk::CreatVssd(); 
	char ch = 'x';
	char prech = 'x';
	size_t index = 0;
	size_t foldernamelength = 0;
	sjh::vssd_pan *MyTop;
	while (1)
	{

		foldernamelength = 0;
		MyTop = MyVssd->GetNowTop();
		MyTop->ShowNowPosForCmd();
		Command.clear();
		bool flag = 0;
		while (1)
		{
			{
				if (ch) prech = ch;
				if (!flag)
				{
					ch = _getch(); flag = 1;
				}

				if (ch == '\t' && prech == ' ')
				{
				aaa:
					if (index < MyVssd->GetNowTop()->GetNowPos()->SubFolders.size())
					{
						std::wstring foldername;
						foldername = MyVssd->GetNowTop()->GetNowPos()->SubFolders[index]->GetName();
						std::cout << sjh::tools_vssd::WStringToString(foldername);
						Command.append(sjh::tools_vssd::WStringToString(foldername));
						foldernamelength = foldername.size();
						prech = 'x';
						index++;
					}
					else
					{
						index = 0;
						if (index < MyVssd->GetNowTop()->GetNowPos()->SubFolders.size())
						{
							std::wstring foldername;
							foldername = MyVssd->GetNowTop()->GetNowPos()->SubFolders[index]->GetName();
							std::cout << sjh::tools_vssd::WStringToString(foldername);
							Command.append(sjh::tools_vssd::WStringToString(foldername));
							foldernamelength = foldername.size();
							prech = 'x';
						}
					}

				}
				else if (ch == '\t')
				{
					if (Command.size())
					{
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
				else if (ch == '\b')
				{
					if (Command.size())
					{
						Command.pop_back();
						putchar('\b');
						putchar(' ');
						putchar('\b');
					}

				}
				else if (ch == '\b')
				{
					puts("\b \b");
				}
				else if (ch == '\r')
				{
					break;
				}
				else
				{
					if (ch)
					{
						putchar(ch);
						Command.push_back(ch);
					}
				}
				flag = 0;
			}
		}
		puts("\n");
		std::wstring LCommand = sjh::tools_vssd::StringToWString(Command);

		sjh::vssd_vcmd::v_cmd_comein(*MyVssd, LCommand);






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
