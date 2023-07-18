#include "LowLevelSystem.h"
#include "CommandConsole.h"
#include <time.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fstream>

#ifdef _WIN32
#pragma comment(lib,"User32.lib")
#include <Windows.h>
#endif

namespace DavinciEngine{

	void Log(const char* fmt, ...)
	{
	    time_t rawtime = NULL;
	    struct tm *timeinfo = nullptr;
		char timeStr[9] = "";
		char text[2048] = "";
        time(&rawtime);
	    timeinfo = localtime(&rawtime);
		strftime(timeStr,9,"%I:%M%p",timeinfo);
		va_list ap = nullptr;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		std::string newMessage;
		newMessage = timeStr;
		newMessage += ": ";
		newMessage += text;
		newMessage += "\n";
	}

	void Warning(const char* fmt, ...)
	{
		char text[2048] = "";
		va_list ap = nullptr;
		if (fmt == nullptr)
			return;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		std::string sMess = "WARNING: ";
		sMess += text;
		Log(sMess.c_str());
	}

	void Error(const char* fmt,...)
	{
		char text[2048] = "";
		va_list ap = nullptr;
		if (fmt == nullptr)
			return;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		std::string sMess = "ERROR: ";
		sMess += text;
		Log(sMess.c_str());
	}

	void FatalError(const char* fmt,...)
	{
		char text[2048] = "";
		va_list ap = nullptr;
		if (fmt == nullptr)
			return;
		va_start(ap, fmt);
		vsprintf(text, fmt, ap);
		va_end(ap);
		std::string sMess = "FATAL ERROR: ";
		sMess += text;
		Log(sMess.c_str());

#ifdef _WIN32
		MessageBox( nullptr, text, "FATAL ERROR", MB_ICONERROR);
#endif
		//WriteLog();
		exit(1);
	}
};
