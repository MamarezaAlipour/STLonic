/**
 * @file conversion.hpp
 * @author Parisa Khaleghi (Parikhaleghi.ir)
 * @brief String conversions are implemented.
 * @version 0.1
 * @date 2022-07-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _STLONIC_CONVERSION_HPP
#define _STLONIC_CONVERSION_HPP

#ifndef STLONIC_SUPPRESS_DEPRECATED_MESSAGES
#define STLONIC_SUPPRESS_DEPRECATED_MESSAGES 1
#endif // end of STLONIC_SUPPRESS_DEPRECATED_MESSAGES

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef _MSVC_LANG
#if _MSVC_LANG < 201703L
#error This libary requires C++17 Standard (Visual Studio 2017).
#endif
#else

#if __cplusplus < 201703
#error This library requires C++17 Standard (GNU g++ version 8.0 or clang++ version 8.0 above)
#endif // end of __cplusplus

#endif // end of _MSVC_LANG

#include <clocale>
#include <cstring>
#include <iostream>
#include <string>
#include <type_traits>
#include <windows.h>

/**
 * @brief Includes subnamespace conversion.
 *
 */
namespace stlonic {
	/**
	 * @brief String conversions are implemented.
	 *
	 */
	namespace conversion {
		/**
		 * @brief Load system default locale for string conversion.
		 *
		 */
		inline void load_default_locale(bool ShowLocaleName = false) {
			// allocate buffer to hold locale name
			std::wstring locale_name(LOCALE_NAME_MAX_LENGTH, L'\0');

			int locale_legnth = GetSystemDefaultLocaleName(&locale_name[0], LOCALE_NAME_MAX_LENGTH);

			// if failed to get locale name, then just return
			if (locale_legnth == 0)
				return;

			// trim trailing buffer
			if (locale_name[locale_legnth] == L'\0')
				locale_name = locale_name.substr(0, locale_legnth - 1);

			_wsetlocale(LC_ALL, locale_name.c_str());

			if (ShowLocaleName)
				std::wcout << L"locale name: " << locale_name << std::endl;
		}

		/**
		 * @brief Converts from std::wstring to std::string with codepage
		 *
		 * If fails, returns empty string, std::string("")
		 *
		 * @param wstr for std::wstring to convert
		 * @param codepage for Code Page, default = CP_UTF8
		 * @return std::string for the converted string
		 */
		inline std::string wstring_to_string(std::wstring const& wstr,
											 unsigned int codepage = CP_UTF8) {
			if (wstr.empty())
				return "";

			int str_len = WideCharToMultiByte(codepage,
											  0, // dwFlag
											  wstr.c_str(), (int)wstr.size(), NULL, 0, NULL, NULL);

			// if failed to compute the byte count of the string
			if (str_len == 0)
				return "";

			// prepare a string buffer to
			// hold the converted string
			// do not +1 to str_len,
			// because std::string manages terminating null
			std::string str(str_len, '\0');

			int converted = WideCharToMultiByte(codepage, 0, wstr.c_str(), (int)wstr.size(),
												&str[0], str_len, NULL, NULL);

			return (converted == 0 ? "" : str);
		}

		/**
		 * @brief Converts std::string to std::wstring using codepage
		 *
		 * If fails, returns empty string, std::wstring(L"")
		 *
		 * @param str for string to convert
		 * @param codepage for Code Page (default CP_UTF8)
		 * @return std::wstring for the converted UTF16 string
		 */
		inline std::wstring string_to_wstring(std::string const& str,
											  unsigned int codepage = CP_UTF8) {
			if (str.empty())
				return L"";

			int wstr_len = MultiByteToWideChar(codepage, 0, str.c_str(), (int)str.size(), NULL, 0);

			// if failed to compute the character length
			if (wstr_len == 0)
				return L"";

			// prepare buffer to hold converted string
			// do not +1 to utf16_len, because std::wstring
			// manages terminating null internally
			std::wstring wstr(wstr_len, L'\0');

			int converted =
				MultiByteToWideChar(codepage, 0, str.c_str(), (int)str.size(), &wstr[0], wstr_len);

			return (converted == 0 ? L"" : wstr);
		}

		/**
		 * @brief Converts UTF16 std::wstring to UTF8 std::string
		 *
		 * If fails, returns empty string, std::string("")
		 *
		 * @param utf16str for UTF16 std::wstring to convert
		 * @return std::string for the converted UTF8 string
		 */
		inline std::string utf16_to_utf8(std::wstring const& utf16str) {
			if (utf16str.empty())
				return "";
			return wstring_to_string(utf16str, CP_UTF8);
		}

		/**
		 * @brief Converts UTF8 std::string to UTF16 std::wstring
		 *
		 * If fails, returns empty string, std::wstring(L"")
		 *
		 * @param utf8str for UTF8 std::string to convert
		 * @return std::wstring for the converted UTF16 string
		 */
		inline std::wstring utf8_to_utf16(std::string const& utf8str) {
			if (utf8str.empty())
				return L"";
			return string_to_wstring(utf8str, CP_UTF8);
		}

		/**
		 * @brief Converts UTF16 (const wchar_t*) to UTF8 (std::string)
		 *
		 * This function converts zero terminated UTF16 or const wchar_t*
		 * to UTF8 std::string. If conversion fails, returns empty string "".
		 *
		 * @param utf16str for UTF16 string to convert to UTF8
		 * @return std::string for UTF8 string, if fails returns empty string ""
		 */
		inline std::string utf16_to_utf8(wchar_t const* utf16str) {
			if (utf16str == nullptr)
				return "";

			// count of character of UTF16 string
			int utf16_len = (int)wcslen(utf16str);
			if (utf16_len < 1)
				return "";

			return utf16_to_utf8(std::wstring(utf16str));
		}

		/**
		 * @brief Converts UTF8 string (const char*) to UTF16 (std::wstring)
		 *
		 * If fails, returns empty string or L"".
		 *
		 * @param utf8str for UTF8 (const char*) to convert
		 * @return std::wstring for the converted UTF16 (std::wstring)
		 */
		inline std::wstring utf8_to_utf16(char const* utf8str) {
			// if utf8str is nullptr, return empty string L""
			if (utf8str == nullptr)
				return L"";

			// count of byte of the string to be converted
			int utf8str_len = (int)strlen(utf8str);
			if (utf8str_len < 1)
				return L"";

			return utf8_to_utf16(std::string(utf8str));
		}

		/**
		 * @brief Converts UTF16 wchar_t to UFT8 char.
		 *
		 * If fails, returns '\0'
		 *
		 * @param utf16_char for UTF16 wchar_t to convert
		 * @return char for the converted UTF8 char
		 */
		inline char utf16_to_utf8(wchar_t const utf16_char) {
			wchar_t src_str[] = {utf16_char, L'\0'};
			auto rlt = utf16_to_utf8(std::wstring(src_str));
			return (rlt.empty() ? '\0' : rlt[0]);
		}

		/**
		 * @brief Converts UTF8 char to UTF16 char.
		 *
		 * If fails, returns L'\0'
		 *
		 * @param utf8_char for UTF8 char to convert
		 * @return wchar_t for the converted UTF16 character
		 */
		inline wchar_t utf8_to_utf16(char const utf8_char) {
			char src_str[] = {utf8_char, '\0'};
			auto rlt = utf8_to_utf16(std::string(src_str));
			return (rlt.empty() ? L'\0' : rlt[0]);
		}

		/////////////////////////////////////////////////

		/**
		 * @brief Converts Windows codepage std::string to utf16 std::wstring
		 *
		 * If fails, returns empty string, std::wstring(L"")
		 *
		 * @param codepage_string for Windows codepage std::string to convert
		 * @return std::wstring for the converted UTF16 std::wstring
		 */
		inline std::wstring windows_codepage_to_utf16(std::string const& codepage_string) {
			return string_to_wstring(codepage_string, CP_ACP);
		}

		/**
		 * @brief Converts UTF16 std::wstring to Windows codepage std::string
		 *
		 * If fails, returns empty string, std::string("")
		 * @param utf16_string for UTF16 std::wstring to convert
		 * @return std::string for the converted Windows codepage string
		 */
		inline std::string utf16_to_windows_codepage(std::wstring const& utf16_string) {
			return wstring_to_string(utf16_string, CP_ACP);
		}

		/**
		 * @brief Converts Windows codepage const char* to UTF16 std::wstring
		 *
		 * If fails, returns empty string, std::wstring(L"")
		 * @param codepage_string for Windows codepage const char* to convert
		 * @return std::wstring for the converted UTF16 string
		 */
		inline std::wstring windows_codepage_to_utf16(char const* codepage_string) {
			if (codepage_string == nullptr)
				return L"";
			if (strlen(codepage_string) < 1)
				return L"";

			return string_to_wstring(std::string(codepage_string), CP_ACP);
		}

		/**
		 * @brief Converts UTF16 const wchar_t* to Windows codepage std::string
		 *
		 * If fails, returns empty string, std::string("")
		 * @param utf16_string for UTF16 const wchar_t* to convert
		 * @return std::string for the converted Windows codepage string
		 */
		inline std::string utf16_to_windows_codepage(wchar_t const* utf16_string) {
			if (utf16_string == nullptr)
				return "";
			if (wcslen(utf16_string) < 1)
				return "";

			return wstring_to_string(std::wstring(utf16_string), CP_ACP);
		}

		/**
		 * @brief Converts Windows codepage std::string to UTF8 std::string
		 *
		 * If fails, returns empty string, std::string("")
		 *
		 * @param codepage_string for Windows codepage std::string to convert
		 * @return std::string for the converted UTF8 string
		 */
		inline std::string windows_codepage_to_utf8(std::string const& codepage_string) {
			auto utf16_str = windows_codepage_to_utf16(codepage_string);

			return (utf16_str.empty() ? "" : utf16_to_utf8(utf16_str));
		}

		/**
		 * @brief Converts Windows codepage const char* to UTF8 std::string
		 *
		 * If fails, return empty string, std::string("")
		 *
		 * @param codepage_string for Windows codepage const char* to convert
		 * @return std::string for the converted UTF8 string
		 */
		inline std::string windows_codepage_to_utf8(char const* codepage_string) {
			if (codepage_string == nullptr)
				return "";
			if (strlen(codepage_string) < 1)
				return "";

			return windows_codepage_to_utf8(std::string(codepage_string));
		}

		/**
		 * @brief Converts UTF8 std::string to Windows codepage string
		 *
		 * If fails, returns empty string, std::string("")
		 *
		 * @param utf8_string for UTF8 std::string to convert
		 * @return std::string for the converted Windows codepage string
		 */
		inline std::string utf8_to_windows_codepage(std::string const& utf8_string) {
			auto utf16_str = utf8_to_utf16(utf8_string);

			return (utf16_str.empty() ? "" : utf16_to_windows_codepage(utf16_str));
		}

		/**
		 * @brief Converts UTF8 const char* to Windows codepage std::string
		 *
		 * If fails, returns empty string, std::string("")
		 *
		 * @param utf8_string for UTF8 const char* to convert
		 * @return std::string for the converted Windows codepage string
		 */
		inline std::string utf8_to_windows_codepage(char const* utf8_string) {
			if (utf8_string == nullptr)
				return "";
			if (strlen(utf8_string) < 1)
				return "";

			return utf8_to_windows_codepage(std::string(utf8_string));
		}

		/**
		 * @brief Converts from source to target.
		 *
		 * @tparam TargetCharType
		 * @tparam SourceCharType
		 * @param str
		 * @return decltype(auto)
		 */
		template <typename TargetCharType, typename SourceCharType>
		decltype(auto) source_to_target(std::basic_string<SourceCharType> const& str) {
			if constexpr (std::is_same_v<TargetCharType, SourceCharType>) {
				return str;
			} else if constexpr (std::is_same_v<SourceCharType, char>) {
				return utf8_to_utf16(str);
			} else {
				return utf16_to_utf8(str);
			}
		}

		inline std::string smart_encode(const char* arg) {
#ifdef _MSC_VER
			return {arg};
#else
			return conversion::utf8_to_windows_codepage(arg);
#endif
		}

		inline std::string smart_encode(const wchar_t* arg) {
			return conversion::utf16_to_windows_codepage(arg);
		}

	} // end of namespace conversion

} // end of namespace stlonic

#endif // end of file _STLONIC_CONVERSION_HPP