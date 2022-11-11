#ifndef __WIN_INTEROP_H__
#define __WIN_INTEROP_H__

#if defined(_WIN32) || defined(_WIN64)
	#include <stdio.h>
	#include <wchar.h>
	#include <windows.h>
	#include <intrin.h>
#else
	#include <x86intrin.h>
#endif

#include "types.hpp"

namespace alc
{
	static bool _win_interop_set = false;

	/// @brief Gets current cpu clock cycle
	/// @return Current cpu clock cycle
	const inline volatile u64 get_cpu_clock_cycle() noexcept
	{
		#ifdef __ALC__INLINE_ASM
			return __rdtsc();
		#else
			return 0;
		#endif
	}

	// allows for showing of colored characters in windows (or windows-based ex: wine) terminals
	// does nothing for linux/unix/mac
	void _allow_win_interop()
	{		
		#if defined(_WIN32) || defined(_WIN64)

		if (alc::_win_interop_set) return;

		HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
		if (hout == INVALID_HANDLE_VALUE) throw "Windows interop err, invalid std handle value. FILE: " __FILE__;

		DWORD dwMode = 0x0;
		if (!GetConsoleMode(hout, &dwMode)) throw "Windows interop err, invalid console mode. FILE: " __FILE__;
		if (!SetConsoleMode(hout, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) throw "Windows interop err, invalid setting of console mode. FILE: " __FILE__;

		#endif
	}
};

#endif // __WIN_INTEROP_H__