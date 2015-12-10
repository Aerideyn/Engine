#pragma once
#include <memory>

namespace Render
{
	class VectorBuffer
	{
	private:

		class BufferHandle
		{
		public:
			BufferHandle();
			BufferHandle(unsigned int Handle);
			~BufferHandle();
			unsigned int GetHandle();
		private:
			unsigned int glHandle;
		};
		std::shared_ptr<BufferHandle> handle;
		bool DataIsValid;
		int floatsPerVector;
		int ElementCount;

	public:
		VectorBuffer();
		VectorBuffer(int NumberOfVectors, int FloatsPerVector, void* Data);
		~VectorBuffer();

		void BindBuffer(int AttributeIndex);
		void DisableBuffer(int AttributeIndex);

		inline int GetElementCount(){ return ElementCount; };
	};

	class IndexBuffer
	{
	private:
		bool DataIsValid = false;
		class IndexBufferHandle
		{
		public:
			IndexBufferHandle();
			IndexBufferHandle(unsigned int Handle);
			~IndexBufferHandle();
			unsigned int GetHandle();
		private:
			unsigned int glHandle;
		};
		std::shared_ptr<IndexBufferHandle> handle;
		int ElementCount;

	public:
		IndexBuffer();
		IndexBuffer(int NuberOfIndicies, int IndiceTypeSize, void* Data);
		~IndexBuffer();
		void BindBuffer();
		inline int GetNumberOfIndicies(){ return ElementCount; };
	};
}