#include "nrpch.h"
#include "Log.h"

namespace Nare
{
	// TODO: This feels wrong against OOP standard. Maybe change this implementation later. The log should have a core and a client console.
	// TODO: It only has a single static console handle. It also will not be very cross platform.
#ifdef NR_PLATFORM_WINDOWS
	static HANDLE coreConsoleHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	Log::Log()
	{
		SetTextColourFromLogPriority(LogPriorityInfo);
	}

	Log::~Log()
	{
		SetTextColourFromLogPriority(LogPriorityInfo);
	}

	std::string Log::RetrieveCurrentTime()
	{
		const auto& t = (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()));
		std::tm p_tm{};
		localtime_s(&p_tm, &t);  // NOLINT(cert-err33-c)
		std::stringstream ss;
		ss << std::put_time(&p_tm, "%T");
		return ss.str();
	}

	void Log::SetTextColourFromLogPriority(LogPriority level)
	{
#ifdef NR_PLATFORM_WINDOWS
		switch (level)
		{
		case LogPriorityTrace:
			SetConsoleTextAttribute(coreConsoleHandle_, 15); // White
			break;
		case LogPriorityInfo:
			SetConsoleTextAttribute(coreConsoleHandle_, 15); // White
			break;
		case LogPriorityWarn:
			SetConsoleTextAttribute(coreConsoleHandle_, 14); // Yellow
			break;
		case LogPriorityError:
			SetConsoleTextAttribute(coreConsoleHandle_, FOREGROUND_RED); 
			break;
		case LogPriorityFatal:
			SetConsoleTextAttribute(coreConsoleHandle_, FOREGROUND_RED);
			break;
		}
#endif

	}
}
