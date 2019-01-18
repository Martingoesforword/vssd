#pragma once 
class vssd_tool {
public:
	 
	static void trim(std::string * s) {

		if (!s->empty())
		{
			s->erase(0, s->find_first_not_of(" "));
			s->erase(s->find_last_not_of(" ") + 1);
		}

	}
	static void trim(std::string & s) {

		if (!s.empty())
		{
			s.erase(0, s.find_first_not_of(" "));
			s.erase(s.find_last_not_of(" ") + 1);
		}

	}
	//输入：四字节整形数据 一个字节型vector引用   目的：将四字节整形数据按大端放入引用中
	static void push4Buint(unsigned int uint4, std::vector<unsigned char> &byte) {
		 
		byte.push_back((uint4 >> 24) & 0x0FF);
		byte.push_back((uint4 >> 16) & 0x0FF);
		byte.push_back((uint4 >> 8) & 0x0FF);
		byte.push_back((uint4) & 0x0FF); 
		return;
	}
	static unsigned int get4Buint(std::vector<unsigned char>::iterator & it) {
		unsigned int a = 0;
		a += *(it + 3) * 1;

		a += *(it + 2) * 128;
		a += *(it + 1) * 128 * 128;
		a += *(it + 0) * 128 * 128 * 128;
		return a;
	}
	static void popstring(std::string  &str,int size,const std::vector<unsigned char>::iterator & it) {
		for (int i = 0; i < size && *(it + i); i++)
		{
			str[i] = *(it+i) ;
		}
		return;
	}
	 
	static void set4Buint(std::vector<unsigned char>::iterator & it, unsigned int uint4) {
		 
		*it = (unsigned char)((uint4 >> 24) & 0x0FF);
		*(it+1) = (unsigned char)((uint4 >> 16) & 0x0FF);
		*(it+2) = (unsigned char)((uint4 >> 8) & 0x0FF);
		*(it+3) = (unsigned char)((uint4) & 0x0FF);
		return;
	}

	static void push0toNspace(unsigned int N, std::vector<unsigned char> &byte) {
		for (int i = 0; i < N; i++)
		{
			byte.push_back(0);
		} 
		return;
	}
	static void pushstring(std::string str, std::vector<unsigned char> &byte) {
		for (int i = 0; i < str.length(); i++)
		{
			byte.push_back(str[i]);
		}
		return;
	}
	static void copyappend(std::vector<unsigned char> &from, std::vector<unsigned char> &to) {
		for (int i = 0; i < from.size(); i++)
		{
			to.push_back(from[i]);
		}
		return;
	}
};
