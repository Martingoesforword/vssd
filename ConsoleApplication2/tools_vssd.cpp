#include "pch.h"  
#include "tools_vssd.h"
namespace sjh {
	namespace tool { 
		namespace math
		{
			bool IsOuShu(int i) { return i % 2 == 0 ? true : false; }
			bool IsJiShu(int i) { return i % 2 == 0 ? false : true; }
		}
		namespace string
		{
			void Split(std::wstring str, std::vector<std::wstring> &ret, std::wstring pattern)
			{
				if (pattern.empty())
				{
					pattern = L" ";
				}
				size_t start = 0, index = str.find_first_of(pattern, 0);
				while (index != str.npos)
				{
					if (math::IsJiShu(SameTimes(str, L"\"", start, index))) 
					{ 
						index = str.find_first_of(pattern, index+1);
						continue;
					} 

					if (start != index)
						ret.push_back(str.substr(start, index - start));
					start = index + 1;
					 
					index = str.find_first_of(pattern, start); 
						
				}
				if (!str.substr(start).empty()) {
					ret.push_back(str.substr(start));
				}

			}
			int SameTimes(std::wstring str, std::wstring pattern, int Start, int End)
			{
				int times = 0;
				size_t index = str.find_first_of(pattern, 0);
				while (index != str.npos && index + pattern.size() - 1 <= End)
				{
					times++;
					Start = index + pattern.size();
					index = str.find_first_of(pattern, Start);
				}

				return times;
			}
			void Trim(std::wstring & s)
			{
				if (!s.empty())
				{
					s.erase(0, s.find_first_not_of(L" "));
					s.erase(s.find_last_not_of(L" ") + 1);
				}
			}
			size_t PushLengthValue(size_t Uint4, std::vector<wchar_t> &Byte)
			{
				size_t Start = Byte.size();
				Byte.push_back((Uint4 >> 16) & 0x0FFFF);
				Byte.push_back((Uint4) & 0xE0FFFF); 
				return Start;
			}
			void PushString(std::wstring Str, std::vector<wchar_t> &Byte)
			{
				PushLengthValue(Str.size(), Byte);
				for (size_t i = 0; i < Str.size(); i++)
				{
					Byte.push_back(Str[i]);
				}
				return;
			}
			void PushTime(std::time_t time, std::vector<wchar_t>& Byte)
			{
				PushLengthValue(time / 4294967296, Byte);
				PushLengthValue(time % 4294967296, Byte);
			}
			void PushWcharVector(std::vector<wchar_t> &StringArray, std::vector<wchar_t> &Byte)
			{
				PushLengthValue(StringArray.size(), Byte);
				for (size_t i = 0; i < StringArray.size(); i++)
				{
					Byte.push_back(StringArray[i]);
				}
				return;
			}



			unsigned int GetLengthValue(const std::vector<wchar_t>& ByteVssd, int &Pos)
			{
				unsigned int LengthValue = 0;
				LengthValue += ByteVssd.at(Pos) * 256 * 256;  Pos++;
				LengthValue += ByteVssd.at(Pos);			Pos++;

				return LengthValue;
			} 
			void GetTime(std::vector<wchar_t>& Byte, std::time_t & time, int & Pos)
			{
				std::time_t a = 0;
				a += GetLengthValue(Byte, Pos) * 4294967296;
				a += GetLengthValue(Byte, Pos);
				time = a;
			} 
			std::wstring GetString(const std::vector<wchar_t>& ByteVssd, int &Pos)
			{
				unsigned int LengthValue = GetLengthValue(ByteVssd, Pos);

				std::wstring ws;

				for (size_t i = 0; i < LengthValue; i++)
				{
					ws.push_back(ByteVssd[Pos++]);
				}
				return ws;
			}
			void GetWcharVector(std::vector<wchar_t> &WcharVector, std::vector<wchar_t> &ByteVssd, int &Pos)
			{
				unsigned int LengthValue = GetLengthValue(ByteVssd, Pos);
				for (size_t i = 0; i < LengthValue; i++)
				{
					WcharVector.push_back(ByteVssd[Pos + i]);
					Pos++;
				}
				return;
			}


			void PushToRealFile(std::wstring JumpTo, std::vector<wchar_t> aSerial)
			{

				unsigned int FileLength = aSerial.size();
				std::ofstream Vssdfile(JumpTo, std::ios::binary);
				if (Vssdfile.is_open())
				{
					Vssdfile.write(((const char*)&FileLength) + 3, 1);
					Vssdfile.write(((const char*)&FileLength) + 2, 1);
					Vssdfile.write(((const char*)&FileLength) + 1, 1);
					Vssdfile.write((const char*)&FileLength, 1);
					int pos = 0;
					Vssdfile.write((const char*)&aSerial[0], aSerial.size() * 2);
					Vssdfile.close();
				}
				else
				{
					std::cout << "Error opening file";
				}
				//按照文档上的格式保存二进制


			}

			void GetFromRealfile(std::wstring GetFrom, std::vector<wchar_t>& aSerial)
			{
				std::ifstream Vssdfile(GetFrom, std::ios::binary);
				if (!Vssdfile.is_open())
				{
					std::cout << "Error opening file"; exit(1);
				}
				else
				{
					char chp = ' ';
					char chq = ' ';
					wchar_t ch;

					Vssdfile.read(&chp, 1);
					Vssdfile.read(&chq, 1);

					ch = chp * 256 * 256 + chq;
					Vssdfile.read(&chp, 1);
					Vssdfile.read(&chq, 1);
					aSerial.push_back(ch);
					ch = chp * 256 * 256 + chq;
					aSerial.push_back(ch);

					unsigned int Bytelength = 0;
					int pos = 0;
					Bytelength = GetLengthValue(aSerial, pos);
					aSerial.clear();

					for (size_t i = 0; i < Bytelength; i++)
					{
						Vssdfile.read(&chp, 1);
						Vssdfile.read(&chq, 1);

						wchar_t ch = chp + chq * 256;
						aSerial.push_back(ch);
					}

					Vssdfile.close();


				}
				//按照文档上的格式读取二进制
			}

			std::wstring GetTimeWString(time_t tm)
			{
				std::tm *ltm = new std::tm();
				localtime_s(ltm, &tm);
				std::wstringstream oss;
				oss << std::setfill(L'0') << std::setw(4) << ltm->tm_year + 1900
					<< "/" << std::setfill(L'0') << std::setw(2) << ltm->tm_mon + 1
					<< "/" << std::setfill(L'0') << std::setw(2) << ltm->tm_mday
					<< "  "
					<< std::setfill(L'0') << std::setw(2) << ltm->tm_hour
					<< ":" << std::setfill(L'0') << std::setw(2) << ltm->tm_min;
				return oss.str();
			}

			std::wstring GetSizeWString(size_t Size)
			{
				std::wstringstream oss;
				if (Size > 1000000000) { goto LAB_MORE1000000000; }
				else if (Size > 1000000) { goto LAB_MORE1000000; }
				else if (Size > 1000) { goto LAB_MORE1000; }
				else { goto LAB_MORE0; }

			LAB_MORE1000000000:
				oss << (Size / 1000000000) % 1000 << L",";
			LAB_MORE1000000:
				oss << (Size / 1000000) % 1000 << L",";
			LAB_MORE1000:
				oss << (Size / 1000) % 1000 << L",";
			LAB_MORE0:
				oss << (Size) % 1000;
				return oss.str();
			}

			std::string GetTimeString(time_t tm)
			{
				return WStringToString(GetTimeWString(tm));
			}

			std::string GetSizeString(size_t Size)
			{
				return WStringToString(GetSizeWString(Size));
			}

			void GetWString(const std::vector<wchar_t>& ByteVssd,std::wstring& a)
			{
				for (size_t i = 0; i < ByteVssd.size(); i++)
				{
					a.push_back(ByteVssd[i]);
				}
			}

			void CheckQuotation(std::wstring& Str)
			{
				if (Str[0] == '\"') Str = Str.substr(1, Str.size() - 2);
			}

			bool IsThisSwitch(const std::wstring & Str, const std::wstring& Pram)
			{
				return (Str.size() == Pram.size() + 1 && Str[0] == '/' && Str.substr(1, Pram.size()) == (Pram));

			}

			bool HasSwitch(const std::wstring & Str)
			{
				return (Str.size() && Str[0] == '/' && Str.size() >= 2);
			}


			std::string WStringToString(const std::wstring &wstrSrc)
			{
				int nLen = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstrSrc.c_str(), -1, NULL, 0, NULL, NULL);
				if (nLen <= 0) return std::string("");

				char* pszDst = new char[nLen + 1];
				if (NULL == pszDst) return std::string("");
				memset(pszDst, 0, nLen + 1);

				WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstrSrc.c_str(), -1, pszDst, nLen, NULL, NULL);
				pszDst[nLen] = 0;

				std::string strTemp(pszDst);
				delete[] pszDst;
				pszDst = NULL;
				return strTemp;

			}

			std::wstring StringToWString(const std::string &strSrc)
			{
				int nLen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strSrc.c_str(), strSrc.size(), 0, 0);
				if (nLen <= 0) return std::wstring(L"");

				WCHAR *pwszDst = new WCHAR[nLen + 1];
				if (NULL == pwszDst) return std::wstring(L"");
				memset(pwszDst, 0, nLen + 1);

				MultiByteToWideChar(CP_ACP, 0, (LPCSTR)strSrc.c_str(), strSrc.size(), pwszDst, nLen);
				pwszDst[nLen] = 0;

				std::wstring wstrTemp(pwszDst);
				delete pwszDst;
				pwszDst = NULL;
				return wstrTemp;
			}
			wchar_t WStringMatch(std::wstring str1, std::wstring str2)
			{
				int slen1 = str1.size();
				int slen2 = str2.size();

				//实际使用时根据strl的长度来动态分配表的内存
				wchar_t matchmap[128][128];
				memset(matchmap, 0, 128 * 128);
				matchmap[0][0] = 1;
				int i, j, k;
				//遍历目标字符串符串
				for (i = 1; i <= slen1; ++i)
				{
					//遍历通配符串
					for (j = 1; j <= slen2; ++j)
					{
						//当前字符之前的字符是否已经得到匹配
						if (matchmap[i - 1][j - 1])
						{
							//匹配当前字符
							if (str1[i - 1] == str2[j - 1] || str2[j - 1] == '?')
							{
								matchmap[i][j] = 1;
								//考虑星号在末尾的情况
								if (i == slen1 && j < slen2)
								{
									for (k = j + 1; k <= slen2; ++k)
									{
										if ('*' == str2[k - 1])
										{
											matchmap[i][k] = 1;
										}
										else
										{
											break;
										}
									}
								}
							}
							else if (str2[j - 1] == '*')
							{
								//遇到星号，目标字符串到末尾都能得到匹配
								for (k = i - 1; k <= slen1; ++k)
								{
									matchmap[k][j] = 1;
								}
							}
						}
					}
					//如果当前字符得到了匹配则继续循环，否则匹配失败
					for (k = 1; k <= slen2; ++k)
					{
						if (matchmap[i][k])
						{
							break;
						}
					}
					if (k > slen2)
					{
						return 0;
					}
				}
				return matchmap[slen1][slen2];
			}
		}
		
	}
}