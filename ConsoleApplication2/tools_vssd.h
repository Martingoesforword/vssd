#pragma once   
#include "pch.h"
namespace sjh {
	namespace tool {
		class stringtools
		{
		public:
			static void				Split(std::wstring str, std::vector<std::wstring> &ret, std::wstring pattern);
			static void				Trim(std::wstring & s);
			static wchar_t			WStringMatch(std::wstring str1, std::wstring str2);
			static std::string		WStringToString(const std::wstring &wstrSrc);
			static std::wstring		StringToWString(const std::string &strSrc);

			static void				PushString(std::wstring Str, std::vector<wchar_t> &Byte);
			static void				PushWcharVector(std::vector<wchar_t> &StringArray, std::vector<wchar_t> &Byte);
			static size_t			PushLengthValue(unsigned int Uint4, std::vector<wchar_t> &Byte);
			static void				PushToRealFile(std::wstring JumpTo, std::vector<wchar_t> aSerial);

			static std::wstring		GetString(const std::vector<wchar_t>& ByteVssd, int &Pos);
			static void				GetWcharVector(std::vector<wchar_t> &WcharVector, std::vector<wchar_t> &ByteVssd, int &Pos);
			static unsigned int		GetLengthValue(const std::vector<wchar_t>& ByteVssd, int &Pos);
			static void				GetFromRealfile(std::wstring GetFrom, std::vector<wchar_t> aSerial);
			static std::wstring		GetTimeWString(time_t tm);
			static std::wstring		GetSizeWString(unsigned int Size);
			static std::string		GetTimeString(time_t tm);
			static std::string		GetSizeString(unsigned int Size);
		};
		 
	}
	
}