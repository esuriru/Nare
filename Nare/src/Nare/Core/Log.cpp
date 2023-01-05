#include "nrpch.h"
#include "Log.h"
#include "Logger.h"

namespace Nare
{
	// static loggers
	std::shared_ptr<Logger> Nare::Log::coreLogger_;
	std::shared_ptr<Logger> Nare::Log::clientLogger_;

#ifdef NR_PLATFORM_WINDOWS
	static HANDLE consoleHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

	void Log::Init()
	{
		// TODO: Make this a better logger (lol). Might make my own logger library as well.
		std::ios::sync_with_stdio(false);

		// TODO: Should not be hardcoded here.
		coreLogger_ = std::make_shared<Logger>("NARE");
		clientLogger_ = std::make_shared<Logger>("APP");

		NR_CORE_WARN("Initialized Log!");
	}

	void Log::Exit()
	{
		SetTextColourFromLogPriority(LogPriorityTrace);
	}

	std::shared_ptr<Logger> Log::GetCoreLogger()
	{
		return coreLogger_;
	}

	std::shared_ptr<Logger> Log::GetClientLogger()
	{
		return clientLogger_;
	}


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

	/**
	 * \brief Static function to change the text colour from the level's priority. This is where the colours are being set.
	 * NOTE: ONLY WORKS IN WINDOWS
	 * \param level: Priority level 
	 */
	void Log::SetTextColourFromLogPriority(LogPriority level)
	{
#ifdef NR_PLATFORM_WINDOWS
		switch (level)
		{
		case LogPriorityTrace:
			SetConsoleTextAttribute(consoleHandle_, 15); // White
			break;
		case LogPriorityInfo:
			SetConsoleTextAttribute(consoleHandle_, FOREGROUND_GREEN); // White
			break;
		case LogPriorityWarn:
			SetConsoleTextAttribute(consoleHandle_, 14); // Yellow
			break;
		case LogPriorityError:
		case LogPriorityFatal:
			SetConsoleTextAttribute(consoleHandle_, FOREGROUND_RED);
			break;
		}
#endif

	}
}
