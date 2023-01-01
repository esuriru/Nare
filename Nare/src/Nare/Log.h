#pragma once
#include "nrpch.h"

namespace Nare
{
	class Log
	{
	public:
		Log();
		~Log();

#pragma region TEMPLATE_LOG_FUNCTIONS
		template<typename... Args>
		static void Trace(const char* msg, Args... args)
		{
			SetTextColourFromLogPriority(LogPriorityTrace);
			printf("[%s]  ", RetrieveCurrentTime().data());
			printf(msg, args...);
			printf("\n");
		}

		template<typename... Args>
		static void Info(const char* msg, Args... args)
		{
			SetTextColourFromLogPriority(LogPriorityInfo);
			printf("[%s]  ", RetrieveCurrentTime().data());
			printf(msg, args...);
			printf("\n");
		}
		
		template<typename... Args>
		static void Warn(const char* msg, Args... args)
		{
			SetTextColourFromLogPriority(LogPriorityWarn);
			printf("[%s]  ", RetrieveCurrentTime().data());
			printf(msg, args...);
			printf("\n");
		}

		template<typename... Args>
		static void Error(const char* msg, Args... args)
		{
			SetTextColourFromLogPriority(LogPriorityError);
			printf("[%s]  ", RetrieveCurrentTime().data());
			printf(msg, args...);
			printf("\n");
		}

		template<typename... Args>
		static void Fatal(const char* msg, Args... args)
		{
			SetTextColourFromLogPriority(LogPriorityFatal);
			printf("[%s]  ", RetrieveCurrentTime().data());
			printf(msg, args...);
			printf("\n");
			// TODO: Might need to end the application?
		}
#pragma endregion TEMPLATE_LOG_FUNCTIONS

	private:
		enum LogPriority
		{
			LogPriorityTrace = 0,
			LogPriorityInfo,
			LogPriorityWarn,
			LogPriorityError,
			LogPriorityFatal
		};
		
		static std::string RetrieveCurrentTime();
		static void SetTextColourFromLogPriority(LogPriority level);

	};
}

#pragma region CORE_LOG_MACROS
#define NR_CORE_TRACE(...) ::Nare::Log::Trace(__VA_ARGS__)
#define NR_CORE_INFO(...) ::Nare::Log::Info(__VA_ARGS__)
#define NR_CORE_WARN(...) ::Nare::Log::Warn(__VA_ARGS__)
#define NR_CORE_ERROR(...) ::Nare::Log::Error(__VA_ARGS__)
#define NR_CORE_FATAL(...) ::Nare::Log::Fatal(__VA_ARGS__)

#pragma endregion CORE_LOG_MACROS

