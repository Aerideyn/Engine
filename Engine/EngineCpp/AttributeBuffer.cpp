#include "AttributeBuffer.h"
#include <GL\glew.h>

//========= Vector Attribute Buffer ========\\

VectorAttributeBuffer::VectorAttributeBuffer() : ElementCount(0)
{
	DataIsValid = false;
}

VectorAttributeBuffer::VectorAttributeBuffer(int NumberOfVectors, int FloatsPerVector, void* Data) : ElementCount(NumberOfVectors)
{
	floatsPerVector = FloatsPerVector;
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, NumberOfVectors * FloatsPerVector * sizeof(float), Data, GL_STATIC_DRAW);
	DataIsValid = true;
}

VectorAttributeBuffer::VectorAttributeBuffer(VectorAttributeBuffer &Other) : ElementCount(Other.ElementCount)
{
	// copy other's data.
	bufferID = Other.bufferID;
	DataIsValid = Other.DataIsValid;
	floatsPerVector = Other.floatsPerVector;

	// invalidate other.
	Other.DataIsValid = false;
	Other.bufferID = -1;
}

void VectorAttributeBuffer::operator=(VectorAttributeBuffer &Other)
{
	// copy other's data.
	bufferID = Other.bufferID;
	DataIsValid = Other.DataIsValid;
	floatsPerVector = Other.floatsPerVector;
	ElementCount = Other.ElementCount;
	// invalidate other.
	Other.DataIsValid = false;
	Other.bufferID = -1;
}

VectorAttributeBuffer::~VectorAttributeBuffer()
{
	if (DataIsValid)
	{
		// release resources
		glDeleteBuffers(1, &bufferID);
	}
}

void VectorAttributeBuffer::BindBuffer(int AttributeIndex)
{
	if (DataIsValid)
	{
		glEnableVertexAttribArray(AttributeIndex);
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
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

void VectorAttributeBuffer::DisableBuffer(int AttributeIndex)
{
	if (DataIsValid)
	{
		// release resources
		glDisableVertexAttribArray(AttributeIndex);
	}
}

// ==================== Index Buffer =====================\\

IndexBuffer::IndexBuffer() : ElementCount(0)
{
	DataIsValid = false;
}

IndexBuffer::IndexBuffer(int NumberOfIndicies, int IndiceTypeSize, void* Data) : ElementCount(NumberOfIndicies)
{
	glGenBuffers(1, &bufferID);
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	glBufferData(GL_ARRAY_BUFFER, NumberOfIndicies * IndiceTypeSize, Data, GL_STATIC_DRAW);
	DataIsValid = true;
}

IndexBuffer::IndexBuffer(IndexBuffer &Other)
{
	// copy other's data.
	bufferID = Other.bufferID;
	DataIsValid = Other.DataIsValid;
	ElementCount = Other.ElementCount;

	// invalidate other.
	Other.DataIsValid = false;
	Other.bufferID = -1;
}

void IndexBuffer::operator=(IndexBuffer &Other)
{
	// copy other's data.
	bufferID = Other.bufferID;
	DataIsValid = Other.DataIsValid;
	ElementCount = Other.ElementCount;

	// invalidate other.
	Other.DataIsValid = false;
	Other.bufferID = -1;
}

IndexBuffer::~IndexBuffer()
{
	if (DataIsValid)
	{
		// release resources.
		glDeleteBuffers(1, &bufferID);
	}
}

void IndexBuffer::BindBuffer()
{
	if (DataIsValid) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
}
