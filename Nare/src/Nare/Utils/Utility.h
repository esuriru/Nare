#pragma once

#include "nrpch.h"

namespace Nare
{
	namespace Utility
	{
		template<typename T1, typename T2>
		bool Contains(T1 container, T2 val)
		{
			return std::find(container.begin(), container.end(), val) != container.end();
		}
	}
}