#pragma once 
class vssd_tool {
public:
	 
	static void Trim(std::string * s) {

		if (!s->empty())
		{
			s->erase(0, s->find_first_not_of(" "));
			s->erase(s->find_last_not_of(" ") + 1);
		}

	}
	static void Trim(std::string & s) {

		if (!s.empty())
		{
			s.erase(0, s.find_first_not_of(" "));
			s.erase(s.find_last_not_of(" ") + 1);
		}

	}
	//输入：四字节整形数据 一个字节型vector引用   目的：将四字节整形数据按大端放入引用中
	static void Push4BUint(unsigned int Uint4, std::vector<unsigned char> &Byte) {
		 
		Byte.push_back((Uint4 >> 24) & 0x0FF);
		Byte.push_back((Uint4 >> 16) & 0x0FF);
		Byte.push_back((Uint4 >> 8) & 0x0FF);
		Byte.push_back((Uint4) & 0x0FF); 
		return;
	}
	//输入：四字节整形数据 一个字节型vector引用   目的：将四字节整形数据按大端放入引用中
	static void Push4BUintForPos(unsigned int Uint4,int Pos, std::vector<unsigned char> &Byte) {

		Byte[Pos] = ((Uint4 >> 24) & 0x0FF);
		Byte[Pos+1] = ((Uint4 >> 16) & 0x0FF);
		Byte[Pos+2] = ((Uint4 >> 8) & 0x0FF);
		Byte[Pos+3] = ((Uint4) & 0x0FF);
		return;
	}
	static unsigned int Get4BUint(const std::vector<unsigned char>& ByteVssd, int Pos, unsigned int &Num) {
		unsigned int a = 0;
		a += ByteVssd.at(Pos + 3);

		a += ByteVssd.at(Pos + 2) * 256;
		a += ByteVssd.at(Pos + 1) * 256 * 256;
		a += ByteVssd.at(Pos + 0) * 256 * 256 * 256;
		Num = a;
		return 1;
	}
	static void GetString(const std::vector<unsigned char>& ByteVssd,int Pos,int Length, std::string &Str) {
		Str.clear();
		int i = 0;
		char ch;
		for (; i < Length && (ch = ByteVssd.at(Pos + i)); i++)
		{
			Str.push_back(ByteVssd[Pos + i]);
		} 
		return;
	}
	static void GetStringAnd0(const std::vector<unsigned char>& ByteVssd, int Pos, int Length, std::string &Str) {

		int i = 0;
		char ch = '0';
		for (; i < Length; i++)
		{
			Str.push_back(ByteVssd[Pos+i]);
		}
		return;
	}
	static void Set4BUint(std::vector<unsigned char>::iterator & It, unsigned int Uint4) {
		 
		*It = (unsigned char)((Uint4 >> 24) & 0x0FF);
		*(It+1) = (unsigned char)((Uint4 >> 16) & 0x0FF);
		*(It+2) = (unsigned char)((Uint4 >> 8) & 0x0FF);
		*(It+3) = (unsigned char)((Uint4) & 0x0FF);
		return;
	}

	static void Push0ToNSpace(unsigned int N, std::vector<unsigned char> &Byte) {
		for (int i = 0; i < N; i++)
		{
			Byte.push_back(0);
		} 
		return;
	}
	static void PushString(std::string Str, std::vector<unsigned char> &Byte) {
		for (int i = 0; i < Str.length(); i++)
		{
			Byte.push_back(Str[i]);
		}
		return;
	}
	static void CopyAppend(std::vector<unsigned char> &From, std::vector<unsigned char> &To) {
		for (int i = 0; i < From.size(); i++)
		{
			To.push_back(From[i]);
		}
		return;
	}
};
