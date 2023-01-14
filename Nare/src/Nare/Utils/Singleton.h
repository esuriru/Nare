#pragma once

/// <summary>
/// Singleton base class
/// </summary>
/// <typeparam name="T">Class to become a singleton</typeparam>
namespace Nare
{
	namespace Utility
	{
		template<typename T>
		class Singleton
		{
		protected:
			Singleton() = default;
			virtual ~Singleton() = default;
		public:
			static T& Instance()
			{
                static T instance;
				return instance;
			}

			// We don't want people to copy the Singleton.
			void operator=(const Singleton&) = delete;
			Singleton(const Singleton&) = delete;
		};
	}
}

