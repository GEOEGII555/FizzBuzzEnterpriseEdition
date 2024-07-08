#pragma once

#include <Windows.h>
#include <tchar.h>
#include <string>

typedef std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> tstring;
typedef std::basic_stringstream<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>> tstringstream;
