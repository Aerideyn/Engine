#include "AttributeBuffers.h"
#include "Window.h"
#include <GL\glew.h>

//========= Index Buffer handle ========\\

Render::IndexBuffer::IndexBufferHandle::IndexBufferHandle(unsigned int handle)
{
	glHandle = handle;
}

Render::IndexBuffer::IndexBufferHandle::~IndexBufferHandle()
{
	glDeleteBuffers(1, &glHandle);
}

GLuint Render::IndexBuffer::IndexBufferHandle::GetHandle()
{
	return glHandle;
}

//========= Vertex Buffer handle ========\\

Render::VectorBuffer::BufferHandle::BufferHandle(unsigned int handle)
{
	glHandle = handle;
}

Render::VectorBuffer::BufferHandle::~BufferHandle()
{
	glDeleteBuffers(1, &glHandle);
}

GLuint Render::VectorBuffer::BufferHandle::GetHandle()
{
	return glHandle;
}

//========= Vector Attribute Buffer ========\\

Render::VectorBuffer::VectorBuffer() : ElementCount(0)
{
	DataIsValid = false;
}

Render::VectorBuffer::VectorBuffer(int NumberOfVectors, int FloatsPerVector, void* Data) : ElementCount(NumberOfVectors)
{
	floatsPerVector = FloatsPerVector;
	unsigned int ID;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, NumberOfVectors * FloatsPerVector * sizeof(float), Data, GL_STATIC_DRAW);
	DataIsValid = true;
	handle = std::shared_ptr<BufferHandle>(new BufferHandle(ID));
}

Render::VectorBuffer::~VectorBuffer()
{}

void Render::VectorBuffer::BindBuffer(int AttributeIndex)
{
	if (DataIsValid)
	{
		glEnableVertexAttribArray(AttributeIndex);
		glBindBuffer(GL_ARRAY_BUFFER, handle->GetHandle());
		glVertexAttribPointer(
			AttributeIndex,     // attribute
			floatsPerVector,    // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);
	}
}

void Render::VectorBuffer::DisableBuffer(int AttributeIndex)
{
	if (DataIsValid)
	{
		glDisableVertexAttribArray(AttributeIndex);
	}
}

// ==================== Index Buffer =====================\\

Render::IndexBuffer::IndexBuffer() : ElementCount(0)
{
	DataIsValid = false;
}

Render::IndexBuffer::IndexBuffer(int NumberOfIndicies, int IndiceTypeSize, void* Data) : ElementCount(NumberOfIndicies)
{
	unsigned int ID;
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, NumberOfIndicies * IndiceTypeSize, Data, GL_STATIC_DRAW);
	DataIsValid = true;
	handle = std::shared_ptr<IndexBufferHandle>(new IndexBufferHandle(ID));
}

Render::IndexBuffer::~IndexBuffer()
{

}

void Render::IndexBuffer::BindBuffer()
{
	if (DataIsValid) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, handle->GetHandle());
}
