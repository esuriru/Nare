#pragma once
#include "nrpch.h"

#include "Nare/Core.h"

namespace Nare
{
	enum class ShaderDataType
	{
		None = 0, 
		Float, Float2, Float3, Float4,
		Mat3, Mat4,
		Int, Int2, Int3, Int4,
		Bool
	};

	static uint32_t ShaderDataTypeSize(ShaderDataType type)
	{
		constexpr uint32_t f_size = sizeof(float);
		switch (type)
		{
			case ShaderDataType::Float: return f_size;
			case ShaderDataType::Float2: return f_size * 2;
			case ShaderDataType::Float3: return f_size * 3;
			case ShaderDataType::Float4: return f_size * 4;

			case ShaderDataType::Mat3: return f_size * 3 * 3;
			case ShaderDataType::Mat4: return f_size * 4 * 4;

			// Int size = float size (4 bytes)
			case ShaderDataType::Int: return f_size;
			case ShaderDataType::Int2: return f_size * 2;
			case ShaderDataType::Int3: return f_size * 3;
			case ShaderDataType::Int4: return f_size * 4;

			// A bool is 1 byte
			case ShaderDataType::Bool: return 1;
			case ShaderDataType::None: break;
		}

		NR_CORE_ASSERT(false, "Unknown ShaderDataType.");
		return 0;
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType Type;
		uint32_t Size;
		uint32_t Offset;
		bool Normalized;

		BufferElement() = default;

		BufferElement(ShaderDataType type, const std::string& name, const bool normalized = false)
			: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized) {}

		uint32_t GetComponentCount() const
		{
			switch (Type)
			{
				case ShaderDataType::Float: return 1;
				case ShaderDataType::Float2: return 2;
				case ShaderDataType::Float3: return 3;
				case ShaderDataType::Float4: return 4;

				case ShaderDataType::Mat3: return 3 * 3;
				case ShaderDataType::Mat4: return 4 * 4;

				case ShaderDataType::Int: return 1;
				case ShaderDataType::Int2: return 2;
				case ShaderDataType::Int3: return 3;
				case ShaderDataType::Int4: return 4;

				case ShaderDataType::Bool: return 1;

				case ShaderDataType::None: break;
			}

			NR_CORE_ASSERT(false, "Unknown ShaderDataType.")
			return 0;
		}
	};

	/**
	 * \brief Layout of the elements in a buffer. Should be constructed when initializing a scene.
	 */
	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			: elements_(elements)
			, stride_(0)
		{
			CalculateOffsetsAndStride();
		}


		BufferLayout() = default;

		inline const std::vector<BufferElement>& GetElements() const
		{
			return elements_;
		}

		inline uint32_t GetStride() const
		{
			return stride_;
		}

		std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
		std::vector<BufferElement>::iterator end() { return elements_.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return elements_.end(); }


	private:
		/**
		 * \brief Cached list of elements. Will get dirtied if modified. Need to recalculate offsets and stride if done.
		 */
		std::vector<BufferElement> elements_;
		uint32_t stride_;

		void CalculateOffsetsAndStride()
		{
			uint32_t offset = 0;
			stride_ = 0;
			for (auto& element : elements_)
			{
				element.Offset = offset;
				offset += element.Size;
				stride_ += element.Size;
			}
		}
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}
		
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const BufferLayout& GetLayout() const = 0;
		virtual void SetLayout(const BufferLayout& layout) = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

}