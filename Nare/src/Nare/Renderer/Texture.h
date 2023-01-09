#pragma once

#include "Nare/Core/Core.h"
#include "Nare/Core/NareMath.h"

namespace Nare
{
	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
        
        virtual void SetData(void* data, uint32_t size) = 0;

		inline virtual Vector2 GetSize()
		{
			return { GetWidth(), GetHeight() };
		}

		virtual void Bind(uint32_t slot = 0) const = 0;

	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& path);
		static Ref<Texture2D> Create(uint32_t width, uint32_t height);
	};
}