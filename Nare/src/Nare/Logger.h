#pragma once
#include "Log.h"

namespace Nare
{
	class Log;

	class Logger
	{
	public:
		explicit Logger(const std::string& name);

#pragma region TEMPLATE_LOCAL_LOG_FUNCTIONS
		template<class T>
		void log(Log::LogPriority level, const T& msg)
		{
			Log::SetTextColourFromLogPriority(level);
			std::cout << "[" << Log::RetrieveCurrentTime() << "]" << " "; // Time
			std::cout << name_ << ": "; // Name
			std::cout << msg << "\n";
		}

		template<typename Arg, typename... Args>
		void log(Log::LogPriority level, Arg&& arg, Args &&... args)
		{
			Log::SetTextColourFromLogPriority(level);
			std::cout << "[" << Log::RetrieveCurrentTime() << "]" << " "; // Time
			std::cout << name_ << ": "; // Name
			std::cout << std::forward<Arg>(arg); // First arg

			using pack_expander = int[];
			static_cast<void>(pack_expander{ 0, (static_cast<void>(std::cout << std::forward<Args>(args)), 0)... }); // Expand the pack then print it

			std::cout << "\n";
		}

		template<typename... Args>
		void Trace(Args&&... args)
		{
			log(Log::LogPriorityTrace, std::forward<Args>(args)...);
		}

		
		template<typename... Args>
		void Info(Args&&... args)
		{
			log(Log::LogPriorityInfo, std::forward<Args>(args)...);
		}
		
		template<typename... Args>
		void Warn(Args&&... args)
		{
			log(Log::LogPriorityWarn, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void Error(Args&&... args)
		{
			log(Log::LogPriorityError, std::forward<Args>(args)...);
		}

		template<typename... Args>
		void Fatal(Args&&... args)
		{
			log(Log::LogPriorityFatal, std::forward<Args>(args)...);
			// TODO: Might need to end the application?
		}
#pragma endregion TEMPLATE_LOCAL_LOG_FUNCTIONS
	private:
		/**
		 * \brief To be printed when logging
		 */
		std::string name_;

		// TODO: Will implement the formatting later. Not an important thing now.
		std::string print_format_;

	};
}
