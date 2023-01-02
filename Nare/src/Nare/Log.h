#pragma once
#include "nrpch.h"

namespace Nare
{
	class Log
	{
	public:
		enum LogPriority
		{
			LogPriorityTrace = 0,
			LogPriorityInfo,
			LogPriorityWarn,
			LogPriorityError,
			LogPriorityFatal
		};

		static void Init();
		static void Exit();


		Log();
		~Log();

	private:
		//static std::unique_ptr<Log> coreInstance_;

		// TODO: Will implement the formatting later. Not an important thing now.
		static std::string s_format;
	public:
#pragma region TEMPLATE_LOG_FUNCTIONS

		// TODO: Spacing between the time and the actual message should be a setting
		template<class T>
		static void log(LogPriority level, const T& msg)
		{
			SetTextColourFromLogPriority(level);
			std::cout << "[" << RetrieveCurrentTime() << "]" << " "; // Time
			std::cout << msg << "\n";
		}

		template<typename Arg, typename... Args>
		static void log(LogPriority level, Arg&& arg, Args &&... args)
		{
			SetTextColourFromLogPriority(level);
			std::cout << "[" << RetrieveCurrentTime() << "]" << " "; // Time
			std::cout << std::forward<Arg>(arg);
			using pack_expander = int[];
			static_cast<void>(pack_expander{ 0, (static_cast<void>(std::cout << std::forward<Args>(args)), 0)... });
			std::cout << "\n";
		}

		template<typename... Args>
		static void Trace(Args&&... args)
		{
			log(LogPriorityTrace, std::forward<Args>(args)...);
		}

		
		template<typename... Args>
		static void Info(Args&&... args)
		{
			log(LogPriorityInfo, std::forward<Args>(args)...);
		}
		
		template<typename... Args>
		static void Warn(Args&&... args)
		{
			log(LogPriorityWarn, std::forward<Args>(args)...);
		}

		template<typename... Args>
		static void Error(Args&&... args)
		{
			log(LogPriorityError, std::forward<Args>(args)...);
		}

		template<typename... Args>
		static void Fatal(Args&&... args)
		{
			log(LogPriorityFatal, std::forward<Args>(args)...);
			// TODO: Might need to end the application?
		}
#pragma endregion TEMPLATE_LOG_FUNCTIONS

	private:
		
		static std::string RetrieveCurrentTime();
		static void SetTextColourFromLogPriority(LogPriority level);

	};
}

#pragma region CORE_LOG_MACROS

#if 1 
#define NR_CORE_TRACE(...) ::Nare::Log::Trace(__VA_ARGS__)
#define NR_CORE_INFO(...) ::Nare::Log::Info(__VA_ARGS__)
#define NR_CORE_WARN(...) ::Nare::Log::Warn(__VA_ARGS__)
#define NR_CORE_ERROR(...) ::Nare::Log::Error(__VA_ARGS__)
#define NR_CORE_FATAL(...) ::Nare::Log::Fatal(__VA_ARGS__)
#endif

#if 0
#define NR_CORE_TRACE(...) ::Nare::Log::log(::Nare::Log::LogPriority::LogPriorityTrace, __VA_ARGS__)
#define NR_CORE_INFO(...)  ::Nare::Log::log(::Nare::Log::LogPriority::LogPriorityInfo, __VA_ARGS__) 
#define NR_CORE_WARN(...)  ::Nare::Log::log(::Nare::Log::LogPriority::LogPriorityWarn, __VA_ARGS__)
#define NR_CORE_ERROR(...) ::Nare::Log::log(::Nare::Log::LogPriority::LogPriorityError, __VA_ARGS__)
#define NR_CORE_FATAL(...) ::Nare::Log::log(::Nare::Log::LogPriority::LogPriorityFatal, __VA_ARGS__)
#endif 

#pragma endregion CORE_LOG_MACROS

