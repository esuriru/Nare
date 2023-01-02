#pragma once
#include "nrpch.h"

namespace Nare
{
	class Logger;

	/**
	 * \brief Global log manager
	 */
	class Log
	{
	// TODO: Spacing between the time and the actual message should be a setting
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

		static std::shared_ptr<Logger> GetCoreLogger();
		static std::shared_ptr<Logger> GetClientLogger();

		Log();
		~Log();


#pragma region TEMPLATE_GLOBAL_LOG_FUNCTIONS

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

	private:

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
#pragma endregion TEMPLATE_GLOBAL_LOG_FUNCTIONS

		friend class Logger;

		static std::string RetrieveCurrentTime();
		static void SetTextColourFromLogPriority(LogPriority level);

		static std::shared_ptr<Logger> coreLogger_;
		static std::shared_ptr<Logger> clientLogger_;
	};
}

// This feels very out of place.
#include "Logger.h"

#pragma region GLOBAL_LOG_MACROS

#define NR_TRACE(...) ::Nare::Log::Trace(__VA_ARGS__)
#define NR_INFO(...) ::Nare::Log::Info(__VA_ARGS__)
#define NR_WARN(...) ::Nare::Log::Warn(__VA_ARGS__)
#define NR_ERROR(...) ::Nare::Log::Error(__VA_ARGS__)
#define NR_FATAL(...) ::Nare::Log::Fatal(__VA_ARGS__)

#pragma endregion GLOBAL_LOG_MACROS

#pragma region CORE_LOG_MACROS

#define NR_CORE_TRACE(...) ::Nare::Log::GetCoreLogger()->Trace(__VA_ARGS__)
#define NR_CORE_INFO(...)  ::Nare::Log::GetCoreLogger()->Info(__VA_ARGS__)
#define NR_CORE_WARN(...)  ::Nare::Log::GetCoreLogger()->Warn(__VA_ARGS__)
#define NR_CORE_ERROR(...) ::Nare::Log::GetCoreLogger()->Error(__VA_ARGS__)
#define NR_CORE_FATAL(...) ::Nare::Log::GetCoreLogger()->Fatal(__VA_ARGS__)

#pragma endregion CORE_LOG_MACROS

#pragma region CLIENT_LOG_MACROS

#define NR_CLIENT_TRACE(...) ::Nare::Log::GetClientLogger()->Trace(__VA_ARGS__)
#define NR_CLIENT_INFO(...)  ::Nare::Log::GetClientLogger()->Info(__VA_ARGS__)
#define NR_CLIENT_WARN(...)  ::Nare::Log::GetClientLogger()->Warn(__VA_ARGS__)
#define NR_CLIENT_ERROR(...) ::Nare::Log::GetClientLogger()->Error(__VA_ARGS__)
#define NR_CLIENT_FATAL(...) ::Nare::Log::GetClientLogger()->Fatal(__VA_ARGS__)

#pragma endregion CLIENT_LOG_MACROS

