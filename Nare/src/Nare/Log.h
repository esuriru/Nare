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

		Log();
		~Log();

	private:

		template<class T, class Char = char>
		struct is_not_loggable : 
			std::integral_constant<bool,
				!std::is_convertible<T, const char*>::value && !std::is_convertible<T, std::basic_string<Char>>::value &&
				!std::is_same<T, const char*>::value && !std::is_same<T, std::basic_string<Char>>::value>
		{};
		template<class T, class Char = char>
		struct is_loggable : 
			std::integral_constant<bool,
				std::is_convertible<T, const char*>::value || std::is_convertible<T, std::basic_string<Char>>::value ||
				std::is_same<T, const char*>::value || std::is_same<T, std::basic_string<Char>>::value>
		{};

		template<class T>
		using IsString = std::enable_if_t<std::is_convertible<T, std::string>::value, bool>;

		template<class T>
		using IsNotString = std::enable_if_t<!std::is_convertible<T, std::string>::value, bool>;

		template<class T, IsString<T> = true>
		static constexpr T print_cast(T msg)
		{
			return std::forward<T>(msg);
		}

		template<class T, IsNotString<T> = true>
		static constexpr const char* print_cast(T msg)
		{
			return msg.data();
		}

		template<typename... Args>
		static void printArgs(const char* format = nullptr, Args &&... args)
		{
			printf(format != nullptr ? format : "%s", print_cast(args)...);
		}

		template<class T, class Char = char>
		using IsLoggable =
			std::enable_if_t<is_loggable<T, Char>::value, bool>;

		template<class T, class Char = char>
		using IsNotLoggable =
			std::enable_if_t<!is_loggable<T, Char>::value, bool>;

		// TODO: I am not able to input the char type (could be wchar) in these packed templates. When the time comes, I'll look at it again.
		template<typename... Args>
		using IsNotLoggableArgs =
			std::enable_if_t<!std::conjunction_v<is_loggable<Args>...>, bool>;

		template<typename... Args>
		using IsLoggableArgs =
			std::enable_if_t<std::conjunction_v<is_loggable<Args>...>, bool>;


	public:
#pragma region TEMPLATE_LOG_FUNCTIONS
		template<class T, IsNotLoggable<T> = true>
		static void log(LogPriority level, const T& msg)
		{
			// Not possible to print;	
		}

		template<class T, IsLoggable<T> = true>
		static void log(LogPriority level, const T& msg)
		{
			SetTextColourFromLogPriority(level);
			printf("[%s] ", RetrieveCurrentTime().data());
			printf(msg);
			printf("\n");
		}

		template<typename... Args, IsLoggableArgs<Args...> = true>
		static void log(LogPriority level, Args &&... args)
		{
			SetTextColourFromLogPriority(level);
			printf("[%s] ", RetrieveCurrentTime().data());
			printArgs(args...);
			//printf(std::forward<Args>(args)...);
			printf("\n");
		}

		template<typename... Args, IsNotLoggableArgs<Args...> = true>
		static void log(LogPriority level, Args &&... args)
		{
			// not printable
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

